//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TModule.h"
#include "Helper.h"
#include "TReport.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTModuleForm *TModuleForm;
//---------------------------------------------------------------------------
__fastcall TTModuleForm::TTModuleForm(TComponent* Owner)
	: TForm(Owner)
{

}

const std::vector<Provider> * providers;
const std::vector<Reciever> * recievers;
const std::vector<Tarif> * tarifs;
const std::vector<Result> * result;

String reportName;

long double max(long double, long double);
void trace(int);
void startOutputWork(String);
void cout(String);
void coutl(String);

long double * memloc(int);
long double ** memloc(int,int);
void memfree(int, long double **);
void memfree(long double *);
void startOptimization(void*);
void showReport(String);
void showRegions(String);
void showStations(String);
boolean checkReportInDB();
	HANDLE Thread;     // Массив потоков
	DWORD tName;
	HANDLE hMutex;

boolean reportIsExists = false;
void clearViews(TStringList *);

std::vector<TStringList *> stringLists;
void initStrings();

void TTModuleForm::setData(const String rep, const std::vector<Provider> *p, const std::vector<Reciever> *r, const std::vector<Tarif> *t, const std::vector<Result> *res)
{
    //_control87(MCW_EM,MCW_EM);
	providers= p;
	recievers = r;
	tarifs = t;
	result = res;

	int p_sum = 0;
	int r_sum = 0;
	for(int i = 0; i < p->size(); i++){
        p_sum+=p->at(i).reserve;
	}

	for(int i = 0; i < r->size(); i++){
		r_sum+=r->at(i).needs;
	}

	reportName = "p"+IntToStr(p_sum) + "_r" + IntToStr(r_sum) + "_" + rep  ;

	reportIsExists = checkReportInDB();

    TModuleForm->MemoInfo->Clear();
	TModuleForm->ProgressBar1->Position = 0;
	TModuleForm->ReportButton->Enabled = false;
	TModuleForm->ReportRecieversButton->Enabled = false;

	initStrings();
	
	clearViews(stringLists[0]);


	if(reportIsExists){
	   showReport("WHERE report_name LIKE '" + reportName + "'  AND value > 0 ORDER BY STATION_PROVIDER");
	} else {
	   TModuleForm->ReportExists->Font->Color = clMaroon;
	   TModuleForm->ComboBox1->Enabled = false;
    }
}

boolean isThreadActive = false;

void startExecute(long double *a, int a_size, long double *b, int b_size, long double **c, long double **x);
//---------------------------------------------------------------------------
void __fastcall TTModuleForm::ButtonStartClick(TObject *Sender)
{



	DWORD result = WaitForSingleObject( Thread, 0);

	cout(result);


	if (isThreadActive==false || result == WAIT_OBJECT_0) {
			// the thread handle is signaled - the thread has terminated
          if(!reportIsExists || MessageBox(Handle, "Отчет за указанный период уже существует. Рассчитать заново?","Отчет существует",  MB_YESNO|MB_ICONQUESTION)  == IDYES ) {


			TModuleForm->Button1->Enabled = true;
			isThreadActive = true;
			int * pointInt = new int(5);
			Thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)startOptimization,pointInt,0,&tName);
			SetPriorityClass(Thread, REALTIME_PRIORITY_CLASS);

			//startOptimization(pointInt);
			}
		}
		else if(result == WAIT_TIMEOUT) {

			 MessageBox(NULL, "Процесс оптимизации уже запущен","Ошибка", MB_ICONSTOP);
			// the thread handle is not signaled - the thread is still alive
		}




}
//---------------------------------------------------------------------------
 void startExecute(long double *a, int a_size, long double *b, int b_size, long double **c, long double **x){

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

	int step = 10;

	long double dzeta = 1.0/std::pow10(step);

	long double h = 10;
	long double delta = 1.0/std::pow10(step);

	long np = 5001;

	long np1 = 1;

	TModuleForm->ProgressBar1->Max = step + 2;
	TModuleForm->ProgressBar1->Position = 0;
	TModuleForm->MemoInfo->Clear();

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
	if (hd < 0) goto _1;    //потребносей больще, чем запасов
	if (hd == 0) goto _2;  //закрытая задача
	if (hd > 0) goto _3;   // a>b -> запасы поставщика больше чем потребности




_1: trace(1);
	n1 = l1 + 1;
	n2 = l2;
	a[n1 - 1] = -hd;
	for (l = 0; l < n2; l++)
		c[n1 - 1][l] = 0;
	goto _4;

_2: trace(2);
	n1 = l1;
	n2 = l2;
	goto _4;

_3:	trace(3);
	n1 = l1;
	n2 = l2 + 1;
	b[n2 - 1] = hd;
	for (k = 0; k < n1; k++)
		c[k][n2 - 1] = 0;

_4:	trace(4);
	niter = 2.e9;
	miter = 10000;

	sa = 0;

	for (k = 0; k < n1; k++)
		sa += a[k] * a[k];

	sb = 0;
	for (l = 0; l < n2; l++)
		sb += b[l] * b[l];

	sa2 = sqrtl(sa + sb);
	s0 = 0;
	sf = 0;

	for (k = 0; k < n1; k++)
		for (l = 0; l < n2; l++) {
			yt[k][l] = a[k] + b[l];
			s0 += yt[k][l] * yt[k][l];
			sf += c[k][l] * c[k][l];
		}

	s0 = sqrtl(s0);
	sf = sqrtl(sf);
	ndp = powl(n1 + n2 + one*n1*n2, one / 8);
	dp = ndp;
	jp = 0;
	pmax = sqrtl(one*(n1 + n2)*n1*n2);
	ng = 0;
	eps = powl(10.0*one, -h + one / dp);
	cpen = sf / s0 / powl(10.0*one, one / dp);

	//MAIN CYCLE
	for (npr = 1; npr <= miter; npr++) {
		eps = eps / powl(10.0 * one, one / dp);
		cpen = cpen * powl(10.0 * one, one / dp);
		if (eps < 3.e-19) dp = 20;
		ndp = dp;
		dcp = 2 * cpen;
		s00 = 0;

		for (k = 0; k < n1; k++)
			for (l = 0; l < n2; l++) {
				y[k][l] = yt[k][l] - c[k][l] / dcp;
				s00 += y[k][l] * y[k][l];
			}

		s00 = sqrtl(s00);
		k0 = niter - 1;
		if (jp < np1 && npr >1) goto _5;
		cout("ITERATION: " + npr);

		if (jp == np1) jp = 0;
	_5: trace(5);
		if (npr > 1) goto _6;

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


		// INNER
		for (n = 1; n <= niter; n++) {

			if (n > 1) goto _7;
			for (k = 0; k < n1; k++)
				for (l = 0; l < n2; l++)
					p[k][l] = (x[k][l] <= 0) ? pmax : 0;

		_7: trace(7);
			if (k1 > np) k1 = 1;
			for (k = 0; k < n1; k++) {
				s11 = 0;
				for (l = 0; l < n2; l++)
					s11 += x[k][l];
				sw1[k] = s11;
			}

			for (l = 0; l < n2; l++) {
				s11 = 0;
				for (k = 0; k < n1; k++)
					s11 += x[k][l];
				sw2[l] = s11;
			}

			s1 = 0;
			for (k = 0; k < n1; k++)
				for (l = 0; l < n2; l++) {
					r[k][l] = sw1[k] + sw2[l] + p[k][l] * x[k][l] - y[k][l];
					s1 += r[k][l] * r[k][l];
				}

			s1n = sqrtl(s1);
			s3 = s1n / s00;

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
			if (s3 - eps < 0) goto _19;
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
					v[k][l] = sw1[k] + sw2[l] + p[k][l] * r[k][l];
				}
			}

			if (n == 1) goto _10;
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
					w[k][l] = sw1[k] + sw2[l] + p[k][l] * z[k][l];
				}
			}

			goto _13;

		_10: trace(10);
			//--->
			if (npr > 1) goto _11;
			//--->
			c2 = s1;
			c3 = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					c3 += v[k][l] * r[k][l];
				}
			}
			goto _12;

		_11: trace(11);
			//--->
			c2 = 0;
			c3 = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					c2 += v[k][l] * r[k][l];
					c3 += v[k][l] * v[k][l];
				}
			}
			//--->

		_12: trace(12);

			c6 = c2 / c3;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					xpr[k][l] = x[k][l];
					x[k][l] -= c6 * r[k][l];
				}
			}

			goto _16;

		_13: trace(13);
			//--->
			if (npr > 1) goto _14;
			//--->

			c1 = 0;
			c2 = s1;
			c3 = 0;
			c4 = 0;
			c5 = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					c1 += w[k][l] * r[k][l];
					c3 += v[k][l] * r[k][l];
					c4 += r[k][l] * z[k][l];
					c5 += w[k][l] * z[k][l];
				}
			}

			goto _15;

		_14: trace(14);

			//--->

			c1 = 0;
			c2 = 0;
			c3 = 0;
			c4 = 0;
			c5 = 0;
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					c1 += w[k][l] * v[k][l];
					c2 += v[k][l] * r[k][l];
					c3 += v[k][l] * v[k][l];
					c4 += w[k][l] * r[k][l];
					c5 += w[k][l] * w[k][l];
				}
			}

			//--->

		_15: trace(15);

			deltan = c5*c3 - c1*c1;
			if (deltan == 0) goto _19;
			alphan = (c1*c2 - c3*c4) / (c5*c3 - c1*c1);
			betan = (c1*c4 - c5*c2) / (c5*c3 - c1*c1);
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					xpr[k][l] = x[k][l];
					x[k][l] += alphan*z[k][l] + betan*r[k][l];
					/*if (x[k][l]>0) {
						try {

							//cout("spcx: " + FloatToStr(spcx));
							//cout("S: " + FloatToStr(c[k][l]) + " * " + FloatToStr(x[k][l]));
						  spcx += c[k][l] * x[k][l];
						} catch (...) {
							cout("spcx: " + FloatToStr(spcx));
							cout("S: " + FloatToStr(c[k][l]) + " * " + FloatToStr(x[k][l]));
						}

					}   */
					s7 = x[k][l];
					s8 = xpr[k][l];
					if (s7 > 0 && s8 <= 0) i++;
					if (s7 <= 0 && s8 > 0) j++;
					if (s7 <= 0) i1++;
				}
			}
			nact = i1;

		_16: trace(16);
			for (k = 0; k < n1; k++) {
				for (l = 0; l < n2; l++) {
					z[k][l] = x[k][l] - xpr[k][l];
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
			//cout("PRINTF: " + (String)n + "/" + (String)niter + " phi = " + FloatToStr(phi) + " res: " + FloatToStr(f));
				cout("PRINTF: " + (String)n + "/" + (String)niter + " phi = " + FloatToStr(phi) + " res: " + IntToStr(getP(phi)));
			TModuleForm->ProgressBar1->Position =  getP(phi);


			if (phi < delta && j2>0) goto _23;
			if (j2 <= 0) goto _9; else goto _22;

		_19: trace(19);
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
	//cout("RESULT: " + FloatToStr(f) + " n1 = " + (String)n1 + " n2 = " + (String)n2);




	int res = 0;

	for (k = 0; k < n1; k++) {
		for (l = 0; l < n2; l++) {
			x[k][l] = max(x[k][l], zero);
			if (x[k][l] > zero) {
				s7 = roundA(x[k][l]);
				k11 = k + 1;
				l11 = l + 1;

				//a2[k] += s7;
				//b2[l] += s7;

				res += s7 * c[k][l];

				//cout("x[" + (String)k11 + "][" + (String)l11 + "] = " + FloatToStr(s7) + "\t\t\t (c = " + FloatToStr(c[k][l]) + ")");
			}
		}
	}

	//cout("RES: " + res);


	 TModuleForm->ProgressBar1->Position = TModuleForm->ProgressBar1->Max;


	//memfree(ni,x);
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


long double max(long double a,long double b)
{

	  return (a > b) ? a : b;


}

void trace(int num) {
	//cout << "goto " << num << endl;
}

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

void cout(String str){
	TModuleForm->MemoInfo->Lines->Add(str);
}

void coutl(String str){
	TModuleForm->MemoInfo->Text = TModuleForm->MemoInfo->Text + str;
}

void startOptimization(void*dummy){

	long double *a, *b, **c;
	long n1, n2;


	a = new long double[providers->size()];
	b = new long double[recievers->size()];

	c = new long double *[providers->size()+1];
		for (int i = 0; i < providers->size()+1; i++) {
			c[i] = new long double[recievers->size()+1];
		}


	for(int i =0; i < providers->size(); i++) {
		a[i] = providers->at(i).reserve;
	}

	for(int i =0; i < recievers->size(); i++) {
		b[i] = recievers->at(i).needs;
	}

	int k = 0;
	int j = recievers->size();
	for(int i =0; i < tarifs->size(); i++){
	   c[i/j][i%j] = tarifs->at(i).cost;;

	   k++;
	}


	int start_time =  clock();

	long double **out = memloc(providers->size()+1,recievers->size()+1);

	startExecute(a,providers->size(),b,recievers->size(),c, out);
	int end_time = clock();
	int search_time = end_time - start_time;


	TModuleForm->MemoInfo->Lines->Add("Время выполнения: " + IntToStr(search_time));

	int sum = 0;

	std::vector<Result> newResult;

    for(int i = 0; i < providers->size(); i++)
		for(int j =0; j < recievers->size(); j++){
				long double val = max(out[i][j], 0);
				int roundVal = roundA(val);

				Result * r = new Result(providers->at(i).name,
				   providers->at(i).id,
				   recievers->at(j).name,
				   recievers->at(j).id,
				   tarifs->at(i+j).cost,
				   roundVal
				   );

				newResult.push_back(*r);

			 }

	//cout("СОхраняю отчет: ");

	TFDQuery *query;
	query = new TFDQuery(NULL);

	query->Connection = Form1->TransportdbConnection;

	query->SQL->Text = "DELETE FROM dbo.Reports  WHERE report_name LIKE '" + reportName + "'";
	query->ExecSQL();

	for(int i =0; i < newResult.size(); i++){
	query->SQL->Text = "INSERT INTO dbo.Reports  (provider, reciever, report_name, value) values (" + IntToStr((int)newResult[i].providerId)
	+"," + IntToStr((int)newResult[i].recieverId) + ",'" + reportName + "'," + IntToStr((int)newResult[i].value) + ")";
	query->ExecSQL();
	//newResult
	}

  query->Close();
  query->Disconnect();
  memfree(providers->size()+1,out);

  
  TModuleForm->Button1->Enabled = false;

  TModuleForm->ReportExists->Font->Color = clMaroon;
  showReport("WHERE report_name LIKE '" + reportName + "'  AND value > 0 ORDER BY STATION_PROVIDER");
  //cout("Конец: " + IntToStr(sum));

}
void __fastcall TTModuleForm::Button1Click(TObject *Sender)
{
	if(Thread!=NULL){
		TerminateThread(Thread, 0);
	}
    TModuleForm->ProgressBar1->Position = 0;
	TModuleForm->Button1->Enabled = false;
}
//---------------------------------------------------------------------------
boolean checkReportInDB(){

   	TFDQuery *query;
	query = new TFDQuery(NULL);

	query->Connection = Form1->TransportdbConnection;

	query->SQL->Text = "SELECT count(*) as ITEMS FROM dbo.Reports  WHERE report_name LIKE '" + reportName + "'";
	query->Open();

	int count = 0;

		while (!query->Eof) {

		count =   query-> FieldByName("ITEMS")->AsInteger;

		query->Next();

	}

	query->Close();
	query->Disconnect();



	return count > 0;

}

void showReport(String where_clause){
	TModuleForm->ReportExists->Font->Color = clGreen;
	TModuleForm->ComboBox1->Enabled = true;
	TModuleForm->ReportButton->Enabled = true;
    TModuleForm->ReportRecieversButton->Enabled = true;

    TFDQuery *query;
	query = new TFDQuery(NULL);
	query->Connection = Form1->TransportdbConnection;
	query->SQL->Text = "SELECT * FROM dbo.Report_region " + where_clause;
	query->Open();


	double summ = 0;
	int count = 0;

		while (!query->Eof) {

		//Form1->ProvidersCount->Caption = Form1->ProvidersCount->Caption.ToInt() + 1;
		//Form1->ReserveCount->Caption = Form1->ReserveCount->Caption.ToInt() + p->reserve;

		count++;

		int counts =  TModuleForm->StringGrid1->RowCount;
		int pos = counts-1;

		TModuleForm->StringGrid1->RowCount = counts+1;

		TModuleForm->StringGrid1->Cells[0][pos] = count;
		TModuleForm->StringGrid1->Cells[1][pos] = query->FieldByName("STATION_PROVIDER")->AsString;
		TModuleForm->StringGrid1->Cells[2][pos] = query->FieldByName("REGION_PROVIDER")->AsString;
		TModuleForm->StringGrid1->Cells[3][pos] = query->FieldByName("STATION_RECIEVER")->AsString;
		TModuleForm->StringGrid1->Cells[4][pos] = query->FieldByName("REGION_RECIEVER")->AsString;
		TModuleForm->StringGrid1->Cells[5][pos] = query->FieldByName("VALUE")->AsString;
		TModuleForm->StringGrid1->Cells[6][pos] = query->FieldByName("COST")->AsString;

		double itog = round(query->FieldByName("TOTAL")->AsFloat);

		summ += itog;

		TModuleForm->StringGrid1->Cells[7][pos] = itog;



		query->Next();

	}

	TModuleForm->TotalSum->Caption = summ;

	query->Close();
	query->Disconnect();




}


void clearViews(TStringList * titles){


        TModuleForm->ReportName->Caption = reportName;

	
		for (int i=0; i < TModuleForm->StringGrid1->RowCount; i++) {
			TModuleForm->StringGrid1->Cols[i]->Clear();
		}
	

		TModuleForm->StringGrid1->Rows[0] = titles ;

		
		TStringList * strings = new TStringList;
		for(int i =0; i < 8; i++)
			strings->Add("");
		TModuleForm->StringGrid1->RowCount = 2;
		TModuleForm->StringGrid1->Rows[1] = strings;
		TModuleForm->TotalSum->Caption = 0;

}

void __fastcall TTModuleForm::ComboBox1Change(TObject *Sender)
{

	clearViews(stringLists[TModuleForm->ComboBox1->ItemIndex]);

	if(TModuleForm->ComboBox1->ItemIndex==0) {
		showReport("WHERE report_name LIKE '" + reportName + "'  AND value > 0 ORDER BY STATION_PROVIDER");
	} else if(TModuleForm->ComboBox1->ItemIndex==1) {
		showRegions("WHERE report_name LIKE '" + reportName + "'  AND value > 0 GROUP BY ID_REGION_PROVIDER, REGION_PROVIDER ORDER BY REGION_PROVIDER");
	} else if(TModuleForm->ComboBox1->ItemIndex==2) {
		showStations("WHERE report_name LIKE '" + reportName + "'  AND value > 0 GROUP BY provider, STATION_PROVIDER ORDER BY STATION_PROVIDER");
	}
}
//---------------------------------------------------------------------------



void showRegions(String where_clause){
	

    TFDQuery *query;
	query = new TFDQuery(NULL);
	query->Connection = Form1->TransportdbConnection;
	query->SQL->Text = "SELECT ID_REGION_PROVIDER, REGION_PROVIDER, sum(value) as 'VALUE', sum(total) as 'TOTAL' FROM dbo.Report_region " + where_clause;
	query->Open();


	double summ = 0;
	int count = 0;

		while (!query->Eof) {

		//Form1->ProvidersCount->Caption = Form1->ProvidersCount->Caption.ToInt() + 1;
		//Form1->ReserveCount->Caption = Form1->ReserveCount->Caption.ToInt() + p->reserve;

		count++;

		int counts =  TModuleForm->StringGrid1->RowCount;
		int pos = counts-1;

		TModuleForm->StringGrid1->RowCount = counts+1;

		TModuleForm->StringGrid1->Cells[0][pos] = count;
		TModuleForm->StringGrid1->Cells[1][pos] = query->FieldByName("REGION_PROVIDER")->AsString;
		TModuleForm->StringGrid1->Cells[2][pos] = query->FieldByName("VALUE")->AsString;
	
		double itog = round(query->FieldByName("TOTAL")->AsFloat);

		summ += itog;

		TModuleForm->StringGrid1->Cells[3][pos] = itog;



		query->Next();

	}

	TModuleForm->TotalSum->Caption = summ;

	query->Close();
	query->Disconnect();




}

void showStations(String where_clause){


    TFDQuery *query;
	query = new TFDQuery(NULL);
	query->Connection = Form1->TransportdbConnection;
	query->SQL->Text = "SELECT provider, STATION_PROVIDER, sum(value) as 'VALUE', sum(total) as 'TOTAL' FROM dbo.Report_region " + where_clause;
	query->Open();


	double summ = 0;
	int count = 0;

		while (!query->Eof) {

		//Form1->ProvidersCount->Caption = Form1->ProvidersCount->Caption.ToInt() + 1;
		//Form1->ReserveCount->Caption = Form1->ReserveCount->Caption.ToInt() + p->reserve;

		count++;

		int counts =  TModuleForm->StringGrid1->RowCount;
		int pos = counts-1;

		TModuleForm->StringGrid1->RowCount = counts+1;

		TModuleForm->StringGrid1->Cells[0][pos] = count;
		TModuleForm->StringGrid1->Cells[1][pos] = query->FieldByName("STATION_PROVIDER")->AsString;
		TModuleForm->StringGrid1->Cells[2][pos] = query->FieldByName("VALUE")->AsString;
	
		double itog = round(query->FieldByName("TOTAL")->AsFloat);

		summ += itog;

		TModuleForm->StringGrid1->Cells[3][pos] = itog;



		query->Next();

	}

	TModuleForm->TotalSum->Caption = summ;

	query->Close();
	query->Disconnect();

}

void initStrings(){

//0
	TStringList * strings0 = new TStringList;
		strings0->Add("N");
		strings0->Add("Станция-поставщик");
		strings0->Add("Регион-поставщик");
		strings0->Add("Станция-получатель");
		strings0->Add("Регион-получатель");
		strings0->Add("Ед. груза");
		strings0->Add("Цена маршрута");
		strings0->Add("Итоговая стоимость");

		//1
	TStringList * strings1 = new TStringList;
		strings1->Add("N");
		strings1->Add("Регион-поставщик");
		strings1->Add("Ед. груза");
		strings1->Add("Итоговая стоимость");

		//2
	TStringList * strings2 = new TStringList;
		strings2->Add("N");
		strings2->Add("Станция-поставщик");
		strings2->Add("Ед. груза");
		strings2->Add("Итоговая стоимость");


	stringLists.push_back(strings0);
	stringLists.push_back(strings1);	
	stringLists.push_back(strings2);

}
void __fastcall TTModuleForm::ReportButtonClick(TObject *Sender)
{
	Form2->setData(reportName);
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TTModuleForm::ReportRecieversButtonClick(TObject *Sender)
{
	Form4->setData(reportName);
	Form4->ShowModal();
}
//---------------------------------------------------------------------------

