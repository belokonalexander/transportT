//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TModule.h"
#include "Helper.h"
#include "TReport.h"
#include "Unit4.h"
#include "TransportModule.h"
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




	std::vector<String> stringData;

	for(int i = 0; i < r->size(); i++){
		if(r->at(i).factory_id>0) {
		   stringData.push_back(IntToStr(r->at(i).factory_id)+IntToStr(r->at(i).needs));
		}
	}



	String factoryrecieversReportHash = "";
    factoryrecieversReportHash = getHash(stringData);
	reportName = factoryrecieversReportHash + "_" + rep  ;



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
          if(!reportIsExists || MessageBox(Handle, "Отчет за указанный период уже существует. Рассчитать заново?","Отчет существует",  MB_YESNO|MB_ICONQUESTION)  == IDYES ) {


			TModuleForm->Button1->Enabled = true;
			isThreadActive = true;
			int * pointInt = new int(5);
			Thread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)startOptimization,pointInt,0,&tName);
			SetPriorityClass(Thread, REALTIME_PRIORITY_CLASS);

			}
		}
		else if(result == WAIT_TIMEOUT) {
			 MessageBox(NULL, "Процесс оптимизации уже запущен","Ошибка", MB_ICONSTOP);
		}




}
//---------------------------------------------------------------------------





void cout(String str){
	TModuleForm->MemoInfo->Lines->Add(str);
}

void coutl(int progress){
	TModuleForm->ProgressBar1->Position =  progress;
}

void startOptimization(void*dummy){

	long double *a, *b, **c;
	long n1, n2;


	std::vector<int> provider_mapped;
	std::vector<int> reciever_mapped;
	std::vector<double> tarif_mapped;

	for(int i =0; i < providers->size(); i++) {
		provider_mapped.push_back(providers->at(i).reserve);
	}

	for(int i =0; i < recievers->size(); i++) {
		reciever_mapped.push_back(recievers->at(i).needs);
	}

	for(int i =0; i < tarifs->size(); i++){
	   tarif_mapped.push_back(tarifs->at(i).cost);
	}


	TransportResolver tr(&provider_mapped,&reciever_mapped,&tarif_mapped);
	tr.Init(cout,coutl);

	int start_time =  clock();

	tr.startExecute();
	long double **out = tr.x;

	int end_time = clock();
	int search_time = end_time - start_time;

	TModuleForm->MemoInfo->Lines->Add("Время выполнения: " + IntToStr(search_time));

	int sum = 0;

	std::vector<Result> newResult;

	//TModuleForm->ProgressBar2->Visible = true;

    for(int i = 0; i < providers->size(); i++)
		for(int j =0; j < recievers->size(); j++){
				long double val = TransportResolver::max(out[i][j], 0);
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

	TFDQuery *query;
	query = new TFDQuery(NULL);

	query->Connection = Form1->TransportdbConnection;

	query->SQL->Text = "DELETE FROM dbo.Reports  WHERE report_name LIKE '" + reportName + "'";
	query->ExecSQL();

	for(int i =0; i < newResult.size(); i++){
	query->SQL->Text = "INSERT INTO dbo.Reports  (provider, reciever, report_name, value) values (" + IntToStr((int)newResult[i].providerId)
	+"," + IntToStr((int)newResult[i].recieverId) + ",'" + reportName + "'," + IntToStr((int)newResult[i].value) + ")";
	query->ExecSQL();
	}

  query->Close();
  query->Disconnect();

  tr.clearOutput();
  
  TModuleForm->Button1->Enabled = false;


  TModuleForm->ReportExists->Font->Color = clMaroon;
  showReport("WHERE report_name LIKE '" + reportName + "'  AND value > 0 ORDER BY STATION_PROVIDER");


}
void __fastcall TTModuleForm::Button1Click(TObject *Sender)
{
	if(Thread!=NULL){
		TerminateThread(Thread, 0);
	}
    TModuleForm->ProgressBar1->Position = 0;
	TModuleForm->Button1->Enabled = false;
	//TModuleForm->ProgressBar2->Visible = false;
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

