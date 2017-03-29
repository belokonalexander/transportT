
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

#include "TabbedView.h"

#include "Helper.h"
#include <map>
#include "TModule.h"
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

 Edit1->Text="01";
Edit2->Text= "02";
Edit4->Text = "01";
Edit5->Text ="02";

initApplicationTabs();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	boolean error = false;
	TEdit * edit;



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


				 initDatabase(date.FormatString("yyyymmdd"), date2.FormatString("yyyymmdd"));
				  //initRecievers(date.DateString(), date2.DateString());



	}
}
//---------------------------------------------------------------------------

void initApplicationTabs(){



	TabbedView::init(4, Form1->Panel7, Form1->Panel10,
						Form1->Panel8, Form1->Panel11,
						Form1->Panel9, Form1->Panel12,
						Form1->Panel6, Form1->Panel13);

	Form1->ProvidersGrid->Cells[0][0] = "N" ;
	Form1->ProvidersGrid->Cells[1][0] = "Поставщик" ;
	Form1->ProvidersGrid->Cells[2][0] = "Идентификатор" ;
	Form1->ProvidersGrid->Cells[3][0] = "Запасы" ;

	Form1->RecieversGrid->Cells[0][0] = "N" ;
	Form1->RecieversGrid->Cells[1][0] = "Потребитель" ;
	Form1->RecieversGrid->Cells[2][0] = "Идентификатор" ;
	Form1->RecieversGrid->Cells[3][0] = "Потребности" ;

	Form1->TarifsGrid->Cells[0][0] = "N" ;
	Form1->TarifsGrid->Cells[1][0] = "Поставщик" ;
	Form1->TarifsGrid->Cells[2][0] = "Потребитель" ;
	Form1->TarifsGrid->Cells[3][0] = "Стоимость" ;

	Form1->ResultsGrid->Cells[0][0] = "N" ;
	Form1->ResultsGrid->Cells[1][0] = "Поставщик" ;
	Form1->ResultsGrid->Cells[2][0] = "Потребитель" ;
	Form1->ResultsGrid->Cells[3][0] = "Стоимость маршрута" ;
	Form1->ResultsGrid->Cells[4][0] = "Всего перевезено" ;
	Form1->ResultsGrid->Cells[5][0] = "Итоговая стоимость" ;

   }

void initDatabase(String from, String to){

		Form1->Memo1->Lines->Add(from + "/" + to);

		providers.clear();
		recievers.clear();
		tarifs.clear();
		results.clear();
        Form1->ExecuteButton->Enabled = false;

		TFDQuery *query;
		query = new TFDQuery(NULL);

		query->Connection = Form1->TransportdbConnection;

		query->SQL->Text = "SELECT * FROM dbo.getProviders(\'" + from + "\',\'" + to + "\') ORDER BY FULLNAME";
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

		Provider * p = new Provider(query->FieldByName("FULLNAME")->AsString,
				   query-> FieldByName("ID_ST_TS_FROM")->AsString.ToInt(),
				   query-> FieldByName("s")->AsString.ToInt());



		providers.push_back(*p);
		initProvidersView(p);
		query->Next();

	}

	query->Close();

	query->SQL->Text = "SELECT * FROM dbo.getRecievers(\'" + from + "\',\'" + to + "\') ORDER BY FULLNAME";
	query->Open();

	while (!query->Eof) {

		Reciever * r = new Reciever(query->FieldByName("FULLNAME")->AsString,
				   query-> FieldByName("ID_ST_TS_TO")->AsString.ToInt(),
				   query-> FieldByName("s")->AsString.ToInt());

		recievers.push_back(*r);
		initRecieversView(r);
		query->Next();
	}

	query->Close();

	query->SQL->Text = "SELECT * FROM dbo.getTarifMatrix(\'" + from + "\',\'" + to + "\') ORDER BY FULLNAME_1, FULLNAME_TO";
	query->Open();

	while (!query->Eof) {

		Tarif * t = new Tarif(query->FieldByName("FULLNAME_1")->AsString,
				   query-> FieldByName("FULLNAME_TO")->AsString,
				   round( query-> FieldByName("COST")->AsFloat));

		tarifs.push_back(*t);
		initTarifsView(t);
		query->Next();
	}

	query->Close();

	query->SQL->Text = "SELECT * FROM dbo.getTransportItog(\'" + from + "\',\'" + to + "\') ORDER BY NAME_SENDER, NAME_RECIPIENT";
	query->Open();

	while (!query->Eof) {

		Result * r = new Result(query->FieldByName("NAME_SENDER")->AsString,
				   query-> FieldByName("NAME_RECIPIENT")->AsString,
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
	Form1->Memo1->Lines->Add("Click");

	TModuleForm->setData(*providers, *recievers, *tarifs, *results);
	TModuleForm->Show();

//	std::vector<Provider> providers;
//	std::vector<Reciever> recievers;
//	std::vector<Tarif> tarifs;
//	std::vector<Result> results;


}
//---------------------------------------------------------------------------

