
#include <vcl.h>
#pragma hdrstop
#include <ctime>
#include <sys/stat.h>
#include "Main.h"
#include <windows.h>
#include<iostream>
#include<stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Math.h>
#include "TabbedView.h"

#include "Helper.h"
#include <map>

#include "TModule.h"
#include "Unit3.h"
#include "HelpPr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

std::vector<Provider> providers;
std::vector<Reciever> recievers;
std::vector<Tarif> tarifs;
std::vector<Result> results;



//std::vector<TabbedView> items;
void initApplicationTabs();
void initDatabase(String, String);
void initRecievers(String, String);

void initProvidersView(Provider*);
void initRecieversView(Reciever*);
void initTarifsView(Tarif*);
void initResultsView(Result*);
      String reportName;
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
struct tm * timeinfo;
time_t rawtime;
 time ( &rawtime );
timeinfo = localtime(&rawtime);

String dtoday = IntToStr(timeinfo->tm_mday);
(dtoday.Length()==1) ? dtoday="0" + dtoday : dtoday;

String dpast = IntToStr(timeinfo->tm_mday-1);
(dpast.Length()==1) ? dpast="0" + dpast : dpast;

String mtoday = IntToStr(timeinfo->tm_mon+1);
(mtoday.Length()==1) ? mtoday="0" + mtoday : mtoday;

/*

Edit1->Text=dpast;
Edit2->Text= mtoday;
Edit4->Text = dtoday;
Edit5->Text = mtoday;
 */

 Edit1->Text="03";
Edit2->Text= "02";
Edit4->Text = "03";
Edit5->Text ="02";

initApplicationTabs();



}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	boolean error = false;
	TEdit * edit;

    Edit8->Text="";

	for(int i=0; i<Form1->Panel2->ControlCount; i++){

	 if(Form1->Panel2->Controls[i]->Name.SubString(1,4)=="Edit"){
		edit = (TEdit*)Form1->Panel2->Controls[i];

		if(edit!=Edit3 && edit!=Edit6) {
				if(edit->Text.Length()>2){
					 error = true;
					 MessageBox(NULL, "Дата выбрана неверно","Ошибка", MB_ICONSTOP);
					 Edit8->Text="Ошибка ввода данных";Edit8->Font->Color=clRed;
					 Edit8->Refresh();
					 break;
				}
		}
	  }
	 }
	 if(!error){

			 TDateTime date, date2;
			 try{
				date = StrToDate((Edit1->Text)+"."+(Edit2->Text)+"."+(Edit3->Text));
				date2 = StrToDate((Edit4->Text)+"."+(Edit5->Text)+"."+(Edit6->Text));
				if(date>date2) 	{
									error = true;
									MessageBox(NULL, "Начальная дата больше конечной","Ошибка", MB_ICONSTOP);
									Edit8->Text="Ошибка ввода даты: начальная дата больше конечной"; Edit8->Font->Color=clRed;
									Edit8->Refresh();
								}
			} catch(...)
			{
				 MessageBox(NULL, "Введена неправильная дата","Ошибка", MB_ICONSTOP);
				 error=true;
				 Edit8->Text="Ошибка ввода даты";Edit8->Font->Color=clRed;
				 Edit8->Refresh();
			}

				 if(!error)
					initDatabase(date.FormatString("yyyymmdd"), date2.FormatString("yyyymmdd"));
				  //initRecievers(date.DateString(), date2.DateString());



	}
}
//---------------------------------------------------------------------------

String to_g;
String from_g;

void initApplicationTabs(){



	TabbedView::init(4, Form1->Panel7, Form1->Panel10,
						Form1->Panel8, Form1->Panel11,
						Form1->Panel9, Form1->Panel12,
						Form1->Panel6, Form1->Panel13);

	Form1->ProvidersGrid->Cells[0][0] = "N" ;
	Form1->ProvidersGrid->Cells[1][0] = "Поставщик" ;
	Form1->ProvidersGrid->Cells[2][0] = "Идентификатор" ;
	Form1->ProvidersGrid->Cells[3][0] = "Запасы, тонны" ;

	Form1->RecieversGrid->Cells[0][0] = "N" ;
	Form1->RecieversGrid->Cells[1][0] = "Потребитель" ;
	Form1->RecieversGrid->Cells[2][0] = "Идентификатор" ;
	Form1->RecieversGrid->Cells[3][0] = "Потребности, тонны" ;

	Form1->TarifsGrid->Cells[0][0] = "N" ;
	Form1->TarifsGrid->Cells[1][0] = "Поставщик" ;
	Form1->TarifsGrid->Cells[2][0] = "Потребитель" ;
	Form1->TarifsGrid->Cells[3][0] = "Стоимость, руб" ;

	Form1->ResultsGrid->Cells[0][0] = "N" ;
	Form1->ResultsGrid->Cells[1][0] = "Поставщик" ;
	Form1->ResultsGrid->Cells[2][0] = "Потребитель" ;
	Form1->ResultsGrid->Cells[3][0] = "Стоимость маршрута, руб." ;
	Form1->ResultsGrid->Cells[4][0] = "Всего перевезено, тонны" ;
	Form1->ResultsGrid->Cells[5][0] = "Итоговая стоимость, руб." ;

   }

void initDatabase(String from, String to){

		to_g = to;
        from_g = from;

		Form1->Memo1->Lines->Add(from + "/" + to);
		reportName= "";
		providers.clear();
		recievers.clear();
		tarifs.clear();
		results.clear();
        Form1->ExecuteButton->Enabled = false;

		TFDQuery *query;
		query = new TFDQuery(NULL);

		query->Connection = Form1->TransportdbConnection;

		query->SQL->Text = "SELECT * FROM dbo.getProviders(\'" + from + "\',\'" + to + "\') ORDER BY P_ST_FULLNAME";
		query->Open();
		//Form1->Memo1->Text = "";

		Form1->ProvidersGrid->RowCount = 2;
		Form1->ProvidersCount->Caption = "0";
		Form1->ReserveCount->Caption = "0";

		Form1->RecieversGrid->RowCount = 2;
		Form1->RecieversCount->Caption = "0";
		Form1->NeedsCount->Caption = "0";

		Form1->TarifsGrid->RowCount = 2;


		Form1->ResultsGrid->RowCount = 2;
		Form1->ResultCost->Caption = 0;



		while (!query->Eof) {

		Provider * p = new Provider(query->FieldByName("P_ST_FULLNAME")->AsString,
				   query-> FieldByName("ID_ST_TS_FROM")->AsString.ToInt(),
				   query-> FieldByName("s")->AsString.ToInt());



		providers.push_back(*p);
		initProvidersView(p);
		query->Next();

	}

	query->Close();

	query->SQL->Text = "SELECT * FROM dbo.getRecievers(\'" + from + "\',\'" + to + "\') ORDER BY R_ST_FULLNAME";
	query->Open();

	while (!query->Eof) {

		Reciever * r = new Reciever(query->FieldByName("R_ST_FULLNAME")->AsString,
				   query-> FieldByName("ID_ST_TS_TO")->AsString.ToInt(),
				   query-> FieldByName("s")->AsString.ToInt(),
				   query-> FieldByName("R_FACTORY_ID")->AsInteger,
				   query-> FieldByName("R_FACTORY_NAME")->AsString);

		recievers.push_back(*r);
		initRecieversView(r);
		query->Next();
	}

	query->Close();

	query->SQL->Text = "SELECT * FROM dbo.getTarifMatrix(\'" + from + "\',\'" + to + "\') ORDER BY P_ST_FULLNAME, R_ST_FULLNAME";
	query->Open();

	while (!query->Eof) {

		Tarif * t = new Tarif(query->FieldByName("P_ST_FULLNAME")->AsString,
				   query-> FieldByName("R_ST_FULLNAME")->AsString,
				   round( query-> FieldByName("COST")->AsFloat));

		tarifs.push_back(*t);
		initTarifsView(t);
		query->Next();
	}

	query->Close();

	query->SQL->Text = "SELECT * FROM dbo.getTransportItog(\'" + from + "\',\'" + to + "\') ORDER BY P_ST_FULLNAME, R_ST_FULLNAME";
	query->Open();

	while (!query->Eof) {

		Result * r = new Result(query->FieldByName("P_ST_FULLNAME")->AsString,
				   query-> FieldByName("R_ST_FULLNAME")->AsString,
				   round( query-> FieldByName("COST")->AsFloat),
				   query-> FieldByName("VALUE")->AsInteger,
				   round( query-> FieldByName("ITOG")->AsFloat)
				   );

		results.push_back(*r);
		initResultsView(r);
		query->Next();
	}

	query->Close();


	Form1->Memo1->Lines->Add("конец");

	Form1->ProvidersGrid->RowCount = Form1->ProvidersGrid->RowCount - 1;
	Form1->RecieversGrid->RowCount = Form1->RecieversGrid->RowCount - 1;
	Form1->TarifsGrid->RowCount = Form1->TarifsGrid->RowCount - 1;
    Form1->ResultsGrid->RowCount = Form1->ResultsGrid->RowCount - 1;

	query->Disconnect();



    reportName = from+to;



	if(results.size()>0)
		Form1->ExecuteButton->Enabled = true;

}


void initProvidersView(Provider * p){


	Form1->ProvidersCount->Caption = Form1->ProvidersCount->Caption.ToInt() + 1;
	Form1->ReserveCount->Caption = Form1->ReserveCount->Caption.ToInt() + p->reserve;



	int counts =  Form1->ProvidersGrid->RowCount;
	int pos = counts-1;

	Form1->ProvidersGrid->RowCount = counts+1;


	Form1->ProvidersGrid->Cells[0][pos] = pos;
	Form1->ProvidersGrid->Cells[1][pos] = p->name;
	Form1->ProvidersGrid->Cells[2][pos] = p->id;
	Form1->ProvidersGrid->Cells[3][pos] = p->reserve;

}

void initRecieversView(Reciever * r){


	Form1->RecieversCount->Caption = Form1->RecieversCount->Caption.ToInt() + 1;
	Form1->NeedsCount->Caption = Form1->NeedsCount->Caption.ToInt() + r->needs;

	int counts =  Form1->RecieversGrid->RowCount;
	int pos = counts-1;

	Form1->RecieversGrid->RowCount = counts+1;

	Form1->RecieversGrid->Cells[0][pos] = pos;
	Form1->RecieversGrid->Cells[1][pos] = r->name;
	Form1->RecieversGrid->Cells[2][pos] = r->id;
	Form1->RecieversGrid->Cells[3][pos] = r->needs;

}

void initTarifsView(Tarif * t){


	int counts =  Form1->TarifsGrid->RowCount;
	int pos = counts-1;

	Form1->TarifsGrid->RowCount = counts+1;

	Form1->TarifsGrid->Cells[0][pos] = pos;
	Form1->TarifsGrid->Cells[1][pos] = t->providerName;
	Form1->TarifsGrid->Cells[2][pos] = t->recieverName;
	Form1->TarifsGrid->Cells[3][pos] = t->cost;

}

void initResultsView(Result * r){

	Form1->ResultCost->Caption = Form1->ResultCost->Caption.ToDouble() + r->itog;

	int counts =  Form1->ResultsGrid->RowCount;
	int pos = counts-1;

	Form1->ResultsGrid->RowCount = counts+1;

	Form1->ResultsGrid->Cells[0][pos] = pos;
	Form1->ResultsGrid->Cells[1][pos] = r->providerName;
	Form1->ResultsGrid->Cells[2][pos] = r->recieverName;
	Form1->ResultsGrid->Cells[3][pos] = r->cost;
	Form1->ResultsGrid->Cells[4][pos] = r->value;
	Form1->ResultsGrid->Cells[5][pos] = r->itog;


}
void __fastcall TForm1::ExecuteButtonClick(TObject *Sender)
{


    Memo1->Lines->Add(reportName);


	TModuleForm->setData(reportName, &providers, &recievers, &tarifs, &results);
	TModuleForm->ShowModal();


}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
   Form3->setData(&recievers);
   Form3->ShowModal();
}
//---------------------------------------------------------------------------


void TForm1::updateRecievers(std::vector<Reciever> *r){

    Form1->RecieversGrid->RowCount = 2;
	Form1->RecieversCount->Caption = "0";
	Form1->NeedsCount->Caption = "0";



	int sum = 0;

	for(int i =0; i < recievers.size(); i++){
		for(int j = 0; j < r->size(); j++){
			if(recievers[i].id == r->at(j).id){
			   recievers[i].needs = r->at(j).needs;
               break;
			}
		}

		sum+=recievers[i].needs;
		initRecieversView(&recievers[i]);
	}


}

void TForm1::updateProviders(std::vector<Provider> *p){

}





void __fastcall TForm1::ComboBox1DropDown(TObject *Sender)
{

		Form1->ComboBox1->Clear();
		TFDQuery *query;
		query = new TFDQuery(NULL);

		query->Connection = Form1->TransportdbConnection;

		query->SQL->Text = "SELECT DISTINCT report_name FROM dbo.reports ORDER BY report_name";
		query->Open();

		TStringList * strings1 = new TStringList;

		while (!query->Eof) {

		strings1->Add(query-> FieldByName("report_name")->AsString);
		query->Next();

		}

	  query->Close();

	   Form1->ComboBox1->Items = strings1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
	String ts =  Form1->ComboBox1->Text;
	std::vector<Provider> a;
	std::vector<Reciever> b;
	std::vector<Tarif> c;
	std::vector<Result> d;

	TModuleForm->setData(ts, &a, &b, &c, &d);
	TModuleForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	if(Form1->ComboBox1->ItemIndex>=0)
	  Form1->SpeedButton1->Enabled = true;
	else Form1->SpeedButton1->Enabled = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
  HelpForm->Show();
}
//---------------------------------------------------------------------------

