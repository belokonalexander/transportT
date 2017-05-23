
#ifndef TRANSPORT_T
#define TRANSPORT_T

#include <vector>

typedef void (__cdecl *MYCBPROC_st) (String);
typedef void (__cdecl *MYCBPROC_db) (int);

class TransportResolver {

public:

	long double **x;


	TransportResolver(const std::vector<int> * providers, const std::vector<int> *recievers, const std::vector<double> *tarifs ){

        this->step = 10;

		x = memloc(providers->size()+1,recievers->size()+1);

		a = new long double[providers->size()];
		b = new long double[recievers->size()];

		c = new long double *[providers->size()+1];
		for (int i = 0; i < providers->size()+1; i++) {
			c[i] = new long double[recievers->size()+1];
		}


		for(int i =0; i < providers->size(); i++) {
			a[i] = providers->at(i);
		}

		for(int i =0; i < recievers->size(); i++) {
			b[i] = recievers->at(i);
		}

        int k = 0;
		int j = recievers->size();
		for(int i =0; i < tarifs->size(); i++){
		   c[i/j][i%j] = tarifs->at(i);;
		   k++;
		}

		a_size = providers->size();
		b_size = recievers->size();



	}

	void setStepH(int step){
        this->step = step;
	}

	void clearOutput(){
		memfree(a_size+1,x);
	}

	void Init(MYCBPROC_st lg, MYCBPROC_db pr)
	{
		m_log = lg;
        m_progress = pr;
	}

    static long double max(long double a,long double b)
	{

	  return (a > b) ? a : b;


	}

	void startExecute(){

    cout("Процесс обработки данных запущен");

	const int l1 = a_size;  //кол-во поставщиков
	const int l2 = b_size;     //кол-во потребителей


	const int ni = a_size+1;
	const int ns = b_size+1;

	const int nas = 1000;

	long k, l, n1, n2, niter, miter, ndp, jp, ng, npr, k0, k1, j2, js, n, i, j, i1, nact, k9, k11, l11;

	long double ss, sc, hd, sa, sb, sa2, s0, sf, dp, pmax, eps, cpen, dcp, s00, s1as, s11, s1, s1n, s3, s2as, sas,
	c1, c2, c3, c4, c5, c6, deltan, betan, spcx, s7, s8, s12, dfeq, phi, f, s10, one, zero, zero_e, alphan;

	long double
	**y = memloc(ni,ns),
	**z = memloc(ni,ns),
	**v = memloc(ni,ns),
	**w = memloc(ni,ns),
	**p = memloc(ni,ns),
	**r = memloc(ni,ns),
	**xpr = memloc(ni,ns),
	**yt = memloc(ni,ns);
	long double * sw1 = memloc(ni),
	*sw2 = memloc(ns),
	*as = memloc(nas);



	long double dzeta = 1.0/std::pow10(step);

	long double h = 10;
	long double delta = 1.0/std::pow10(step);

	long np = 5001;

	long np1 = 1;



	n1 = a_size;
	n2 = b_size;

    zero = 0;
	zero_e = 0.0001;
	one = 1.;
	ss = 0;

	for (k = 0; k < l1; k++) {
		ss += a[k];
	}

	sc = 0;
	for (l = 0; l < l2; l++)
		sc += b[l];

	hd = ss - sc;


	if (fabsl(hd / (ss + sc)) < delta / 10.0) goto _2;
	if (hd < 0) goto _1;    //потребностей больще, чем запасов
	if (hd == 0) goto _2;  //закрытая задача
	if (hd > 0) goto _3;   // a>b -> запасы поставщика больше чем потребности




_1: trace(1); // приводим к закрытой задаче
	n1 = l1 + 1;
	n2 = l2;
	a[n1 - 1] = -hd;
	for (l = 0; l < n2; l++)
		c[n1 - 1][l] = 0;
	goto _4;

_2: trace(2); // ничего не делаем, задача уже закрыта
	n1 = l1;
	n2 = l2;
	goto _4;

_3:	trace(3);	// приводим к закрытой задаче
	n1 = l1;
	n2 = l2 + 1;
	b[n2 - 1] = hd;
	for (k = 0; k < n1; k++)
		c[k][n2 - 1] = 0;

_4:	trace(4);
	niter = 2.e9;	//кол-во итераций внутреннего цикла
	miter = 10000;	//кол-во итераций внешнего цикла

	sa = 0;
	for (k = 0; k < n1; k++)
		sa += a[k] * a[k];

	sb = 0;
	for (l = 0; l < n2; l++)
		sb += b[l] * b[l];

	sa2 = sqrtl(sa + sb);	//норма - ||y||
	s0 = 0;
	sf = 0;

	for (k = 0; k < n1; k++)
		for (l = 0; l < n2; l++) {
			yt[k][l] = a[k] + b[l];		//сумма соответствующих исходных векторов поставщик-потребитель (запас поставщика-k = 10, потребность потреб-l = 5) -> 15
			s0 += yt[k][l] * yt[k][l];	//квадрат суммы
			sf += c[k][l] * c[k][l];	//квадрат тарифов
		}

	s0 = sqrtl(s0); 	//норма ||y0||
	sf = sqrtl(sf);		//норма ||c||
	ndp = powl(n1 + n2 + one*n1*n2, one / 8);	//параметр ню
	dp = ndp;
	jp = 0;
	pmax = sqrtl(one*(n1 + n2)*n1*n2);
	ng = 0;
	eps = powl(10.0*one, -h + one / dp);
	cpen = sf / s0 / powl(10.0*one, one / dp);

	//MAIN CYCLE
	for (npr = 1; npr <= miter; npr++) {
		eps = eps / powl(10.0 * one, one / dp);		//параметр d (2.5)
		cpen = cpen * powl(10.0 * one, one / dp);	//параметр e (2.6)
		if (eps < 3.e-19) dp = 20;
		//ndp = dp;
		dcp = 2 * cpen;
		s00 = 0;

		for (k = 0; k < n1; k++)
			for (l = 0; l < n2; l++) {
				y[k][l] = yt[k][l] - c[k][l] / dcp;	// уменьшаем сумму на тариф/коэфициент
				s00 += y[k][l] * y[k][l];			// квадрат новой суммы
			}

		s00 = sqrtl(s00);	//новое значение ||y||
		k0 = niter - 1;
		if (jp < np1 && npr >1) goto _5;


		if (jp == np1) jp = 0;
	_5: trace(5);
		if (npr > 1) goto _6;


		//первый проход, x0 = 0, как и предыдущий проход xpr
		for (k = 0; k < n1; k++)
			for (l = 0; l < n2; l++) {
				x[k][l] = 0;
				xpr[k][l] = 0;
			}
	_6: trace(6);
		k1 = 0;
		j2 = 0;

		//--->
		for (js = 0; js < nas; js++) {
			as[js] = 0;
		}
		//--->
		s1as = 0;


		// - - -- - -- - В Н У Т Р Е Н Н И Й    Ц И К Л - - -- - -- -

		for (n = 1; n <= niter; n++) {

			if (n > 1) goto _7;

			//первая итерация внутреннего цикла - p[k][l] - тот же x[k][l] без отрицательных элементов и pmax вместо положительных
			for (k = 0; k < n1; k++)
				for (l = 0; l < n2; l++)
					p[k][l] = (x[k][l] <= 0) ? pmax : 0;

		_7: trace(7);
			if (k1 > np) k1 = 1;
			for (k = 0; k < n1; k++) {
				s11 = 0;
				for (l = 0; l < n2; l++)
					s11 += x[k][l];
				sw1[k] = s11; 		// sw1[0] - сумма груза, отправленная (всем) 1м поставщиком
			}

			for (l = 0; l < n2; l++) {
				s11 = 0;
				for (k = 0; k < n1; k++)
					s11 += x[k][l];
				sw2[l] = s11; 		// sw1[0] - сумма груза, полученная (всеми) 1м потребителем
			}

			s1 = 0;
			for (k = 0; k < n1; k++)
				for (l = 0; l < n2; l++) {
					r[k][l] = sw1[k] + sw2[l] + p[k][l] * x[k][l] - y[k][l];	//вектор невязки
					s1 += r[k][l] * r[k][l];
				}

			s1n = sqrtl(s1);	// ||r||
			s3 = s1n / s00;		// вычисляем ||rn||/||y||

			//--->
			s2as = fabs(as[2] - as[0]);
			for (js = 1; js < nas; js++)
				as[js - 1] = as[js];
			as[nas - 1] = s1n;
			s1as += fabs(as[nas - 1] - as[nas - 3]) - s2as;
			if (n < nas) goto _8;
			sas = s1as / dzeta / s00 / max(eps, s3);
			if (sas < 1) goto _19;
			if (npr > 1 && n > 3.e4) goto _19;

			//--->

		_8: trace(8);
			if (k1 == np) goto _17;

		_9: trace(9);
			if (s3 - eps < 0) goto _19;	//проверяется условие (3.1) ||rn||/||y|| < eps
			j2 = 0;
			i = 0;
			j = 0;
			i1 = 0;

			for (k = 0; k < n1; k++) {
				s11 = 0;
				for (l = 0; l < n2; l++) {
					s11 += r[k][l];
				}
				sw1[k] = s11;
			}



			for (l = 0; l < n2; l++) {
				s11 = 0;
				for (k = 0; k < n1; k++) {
					s11 += r[k][l];
				}
				sw2[l] = s11;
			}

			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					v[k][l] = sw1[k] + sw2[l] + p[k][l] * r[k][l]; //расчет D0r0
				}
			}

			if (n == 1) goto _10;

			//если не первая итерация внутреннего цикла

			for (k = 0; k < n1; k++) {
				s11 = 0;
				for (l = 0; l < n2; l++) {
					s11 += z[k][l];
				}
				sw1[k] = s11;
			}

			for (l = 0; l < n2; l++) {
				s11 = 0;
				for (k = 0; k < n1; k++) {
					s11 += z[k][l];
				}
				sw2[l] = s11;
			}

			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					w[k][l] = sw1[k] + sw2[l] + p[k][l] * z[k][l];	//расчет Dnzn
				}
			}

			goto _13;

		_10: trace(10);

			//если первая итерация внутреннего цикла

			if (npr > 1) goto _11;

			//расчет [(r0,r0) и (D0r0,r0)] для первой итерации
			c2 = s1;						//r0r0r
			c3 = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					c3 += v[k][l] * r[k][l]; //(D0r0,r0)
				}
			}
			goto _12;

		_11: trace(11);
			//расчет [(D0r0,D0r0) и (D0r0,r0)] для последующих итераций
			c2 = 0;
			c3 = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					c2 += v[k][l] * r[k][l]; //(D0r0,r0)
					c3 += v[k][l] * v[k][l]; //(D0r0,D0r0)
				}
			}
			//--->

		_12: trace(12);
			//расчет x1 по x0 для метода невязки
			c6 = c2 / c3;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					xpr[k][l] = x[k][l];	//сохраняем предыдущий результат
					x[k][l] -= c6 * r[k][l];	//формируем новый план перевозок x1, x0 здесь нулевой вектор
				}
			}

			goto _16;

		_13: trace(13);
			//--->
			if (npr > 1) goto _14;
			//--->
			//первая итерация - СМГС
			c1 = 0;
			c2 = s1;				// rnrn
			c3 = 0;
			c4 = 0;
			c5 = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					c1 += w[k][l] * r[k][l];	//dnzn,rn
					c3 += v[k][l] * r[k][l];	//dnrn,rn
					c4 += r[k][l] * z[k][l];	//zn,rn
					c5 += w[k][l] * z[k][l];	//dnzn,zn
				}
			}

			goto _15;

		_14: trace(14);
			//не первая итерация
			//--->

			c1 = 0;
			c2 = 0;
			c3 = 0;
			c4 = 0;
			c5 = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					c1 += w[k][l] * v[k][l];	//dnzn,dnrn
					c2 += v[k][l] * r[k][l];	//dnrn,rn
					c3 += v[k][l] * v[k][l];	//dnrn,dnrn
					c4 += w[k][l] * r[k][l];	//dnzn,rn
					c5 += w[k][l] * w[k][l];	//dnzn,dnzn
				}
			}

			//--->

		_15: trace(15);

			deltan = c5*c3 - c1*c1;				// расчет delta n (разный в двух методах)
			if (deltan == 0) goto _19;

			alphan = (c1*c2 - c3*c4) / (c5*c3 - c1*c1);	//alpha
			betan = (c1*c4 - c5*c2) / (c5*c3 - c1*c1);	//beta
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					xpr[k][l] = x[k][l];

					//приращение и формирование нового плана
					x[k][l] += alphan*z[k][l] + betan*r[k][l];

					s7 = x[k][l];
					s8 = xpr[k][l];
					if (s7 > 0 && s8 <= 0) i++;
					if (s7 <= 0 && s8 > 0) j++;
					if (s7 <= 0) i1++;
				}
			}
			nact = i1; //кол-во активных элементов (т.е что меньше или равны нулю)

		_16: trace(16);
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					z[k][l] = x[k][l] - xpr[k][l];			//новый расчет zn по xn и xpr (на предыдущем шаге)
					p[k][l] = (x[k][l] <= 0) ? pmax : 0;
				}
			}
			goto _21;

		_17: trace(17);
			s11 = 0;
			for (k = 0; k < n1; k++) {
				s12 = 0;
				for (l = 0; l < n2; l++) {
					s12 += max(x[k][l], zero);
				}
				s11 += (s12 - a[k]) * (s12 - a[k]);
			}

			dfeq = s11;
			s12 = 0;

			for (l = 0; l < n2; l++) {
				s11 = 0;
				for (k = 0; k < n1; k++) {
					s11 += max(x[k][l], zero);
				}
				s12 += (s11 - b[l]) * (s11 - b[l]);
			}

			//расчет ||rn||
			dfeq = sqrtl(dfeq + s12);
			phi = dfeq / sa2;
			if (j2 == 1) goto _20;

		_18: trace(18);
			f = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					if (x[k][l]>0)
						f += c[k][l] * x[k][l];
				}
			}

			s10 = 0;

			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					s10 += x[k][l] * x[k][l];
				}
			}

			s10 = sqrtl(s10);
			cout("Текущее значение phi:");
			cout( FloatToStr(phi));
			cout("[выполнено: " + IntToStr(getP(phi)-1) + " из " + (step+1) + "]");

			progress(phi);



			if (phi < delta && j2>0) goto _23;
			if (j2 <= 0) goto _9; else goto _22;

		_19: trace(19);
			//первое условие соблюдено
			j2 = 1;
			goto _17;

		_20: trace(20);
			if (phi < delta) goto _18;
			if (++jp < np1) goto _22;
			goto _18;

		_21: trace(21);
			k9 = n;
			ng++;
			k1++;
		}
	_22:	trace(22);
		;
	}

_23: trace(23);

	int res = 0;

	for (k = 0; k < n1; k++) {
		for (l = 0; l < n2; l++) {
			x[k][l] = max(x[k][l], zero);
			if (x[k][l] > zero) {
				s7 = roundA(x[k][l]);
				k11 = k + 1;
				l11 = l + 1;

				res += s7 * c[k][l];

						}
		}
	}



	memfree(ni,y);
	memfree(ni,z);
	memfree(ni,v);
	memfree(ni,w);
	memfree(ni,p);
	memfree(ni,r);
	memfree(ni,xpr);
	memfree(ni,yt);

	memfree(sw1);
	memfree(sw2);
	memfree(as);

 }


private:
	int step; // h - коэфициент, отвечающий за точность вычислений; чем меньше, тем быстрее работает алгоритм
   //поставщики, потребители, матрица тарифов, результат
   long double *a, *b, **c,  a_size, b_size;

   MYCBPROC_st m_log; 						//log callback
   MYCBPROC_db m_progress; 				  	//progress callback



   void memfree(int size, long double ** a){
		for (int i = 0; i < size; ++i)
			delete [] a[i];
		delete [] a;
	}

	void memfree(long double * a){
		delete[] a;
	}


	long double * memloc(int a){

		long double * array = new long double[a];

		for(int i =0; i < a; i++)
			array[i] = 0;

	   	return array;
	}

	long double ** memloc(int a,int b){
	   long double ** result;
	   result = new long double *[a];
			for (int i = 0; i < a; i++) {
				result[i] = new long double[b];
			}

	   for(int i =0; i < a; i++)
			for(int j =0; j < b; j++)
				result[i][j] = 0;

	   return result;
	}



	static int getP(double d)
	{
    int i =0;

		while (pow(d,2) < 10)
		{
			d*= 10;
			i++;
		}

	return i;
	}

	void trace(int num) {
      //for trace callback
	}


	void cout(String str){
		m_log(str);
	}

	void progress(double phi){
        m_progress(getP(phi));
	}

};


#endif
