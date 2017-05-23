//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "DBModels.h"
#include "Helper.h"

#include "TabbedView2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
String reportName;
std::vector<Reciever> factoryRecievers;
int selectedIndex = -1;
void fillData(int index);
void fillGrapgh();
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

TStringList * strings1;

void TForm4::setData(String r){

	  reportName = r;
	  Form4->Caption = "Отчет: " + reportName;
      Form4->Panel2->Visible = false;

	  factoryRecievers.clear();
	  //Form4->ListBox1->Items =  strings1;

	TFDQuery *query;
	query = new TFDQuery(NULL);

	query->Connection = Form1->TransportdbConnection;

	query->SQL->Text = "SELECT DISTINCT R_FACTORY_ID, R_FACTORY_NAME FROM getSummary('" + reportName + "') WHERE R_FACTORY_ID IS NOT NULL";
	query->Open();

	while (!query->Eof) {


		Reciever * r = new Reciever(query->FieldByName("R_FACTORY_ID")->AsInteger,
											   query-> FieldByName("R_FACTORY_NAME")->AsString
											   );

		factoryRecievers.push_back(*r);

	   query->Next();

	}

	query->Close();
	query->Disconnect();


		 strings1 = new TStringList;

		 for(int i =0; i < factoryRecievers.size(); i++){
			strings1->Add(factoryRecievers[i].factory_str);
		 }

		 Form4->ListBox1->Items =  strings1;


	TabbedView2::init(2, Form4->Panel6, Form4->Panel7,
						Form4->Panel8, Form4->Panel9
						);

}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm4::ListBox1Click(TObject *Sender)
{
	if(selectedIndex!=Form4->ListBox1->ItemIndex){
		selectedIndex=Form4->ListBox1->ItemIndex;
		fillData(selectedIndex);
	}
}

bool checkBoxIsCreated = false;

std::vector<ReportSummary> factorySummary;
	std::vector<int> regions_values;
	int sum_regions_1 = 0;
	std::vector<int> regions_was_values;
	 int sum_regions_2 = 0;
		TStringList* regions = new TStringList;
//---------------------------------------------------------------------------
 void fillData(int index){
	Form4->Panel2->Visible = true;
	Form4->SelectedFactory->Caption = factoryRecievers[index].factory_str;


	regions_values.clear();
	regions_was_values.clear();

    regions->Clear();
	factorySummary.clear();
	sum_regions_1 = 0;
    sum_regions_2 = 0;

	//получаю регионы
    TFDQuery *query;
	query = new TFDQuery(NULL);
	query->Connection = Form1->TransportdbConnection;


	query->SQL->Text = "SELECT * FROM getSummary('" + reportName + "') WHERE R_FACTORY_ID = " + IntToStr(factoryRecievers[index].factory_id);


	query->Open();
	while (!query->Eof) {


		ReportSummary * rs = new ReportSummary(query->FieldByName("id")->AsInteger,
											   query-> FieldByName("provider")->AsInteger,
											   query-> FieldByName("reciever")->AsInteger,
											   query-> FieldByName("value")->AsInteger,
											   query-> FieldByName("ID_REGION_PROVIDER")->AsInteger,
											   query-> FieldByName("REGION_PROVIDER")->AsString,
											   query-> FieldByName("ID_REGION_RECIEVER")->AsInteger,
											   query-> FieldByName("REGION_RECIEVER")->AsString,
											   query-> FieldByName("STATION_RECIEVER")->AsString,
											   query-> FieldByName("STATION_PROVIDER")->AsString,

											   query-> FieldByName("P_FACTORY_ID")->AsInteger,
											   query-> FieldByName("R_FACTORY_ID")->AsInteger,

											   query-> FieldByName("P_FACTORY_NAME")->AsString,
											   query-> FieldByName("R_FACTORY_NAME")->AsString,

											   round( query-> FieldByName("COST")->AsFloat),
											   round( query-> FieldByName("TOTAL")->AsFloat),
											   query-> FieldByName("WAS_VALUE")->AsInteger,
											   query-> FieldByName("DIF")->AsInteger
											   );

		factorySummary.push_back(*rs);

	   query->Next();

	}

	query->Close();
	query->Disconnect();

	//по регионам


	for(int i = 0; i < factorySummary.size() ;i++){

		 int index = regions->IndexOf(factorySummary[i].region_provider);

		 if(index<0) {
			regions->Add(factorySummary[i].region_provider);
			regions_values.push_back(factorySummary[i].value);
			regions_was_values.push_back(factorySummary[i].was_value);
		 } else {
			regions_values[index]+=factorySummary[i].value;
			regions_was_values[index]+=factorySummary[i].was_value;
		 }

		 sum_regions_1+= factorySummary[i].was_value;
		 sum_regions_2+= factorySummary[i].value;
    }


	Form4->CheckListBox1->Items = regions;

	Form4->CheckListBox1->CheckAll(true);

	checkBoxIsCreated = true;

	fillGrapgh();
}

void fillGrapgh(){

	Form4->Series1->Clear();
	Form4->Series2->Clear();
	Form4->BarSeries2->Clear();
	Form4->PieSeries1->Clear();

	Form4->Series1->Title="Исходные данные";
	Form4->Series2->Title="Данные после оптимизации";

	Form4->BarSeries2->Title = "Исходные данные";


	 Form4->Chart1->Title->Text->Clear();

	 String dt1 = reportName.SubString(reportName.Pos("_")+1,8);
	 TDateTime date1 = StrToDate(dt1.SubString0(6,2)+"." + dt1.SubString0(4,2) + "." + dt1.SubString0(0,4));

	 String dt2 = reportName.SubString(reportName.Pos("_")+9,8);
	 TDateTime date2 = StrToDate(dt2.SubString0(6,2)+"." + dt2.SubString0(4,2) + "." + dt2.SubString0(0,4));

	 if(date1==date2)
		Form4->Chart1->Title->Text->Add("Отчет по предприятию " + Form4->SelectedFactory->Caption + " за " + DateToStr(date1));
	 else
		Form4->Chart1->Title->Text->Add("Отчет по предприятию " + Form4->SelectedFactory->Caption + " за период с " + DateToStr(date1) + " по " + DateToStr(date2));


	Form4->Chart2->Title->Text->Clear();

	 if(date1==date2){
		Form4->Chart2->Title->Text->Add("Исходные данные по поставке товара для предприятия ");
		Form4->Chart2->Title->Text->Add(Form4->SelectedFactory->Caption + " за " + DateToStr(date1));

	 }
	 else {
		Form4->Chart2->Title->Text->Add("Исходные данные по поставке товара для предприятия ");
		Form4->Chart2->Title->Text->Add(Form4->SelectedFactory->Caption + " за период с " + DateToStr(date1) + " по " + DateToStr(date2));
	 }

	Form4->Chart3->Title->Text->Clear();

		 if(date1==date2){
		Form4->Chart3->Title->Text->Add("Оптимизированные данные по поставке товара для предприятия ");
		Form4->Chart3->Title->Text->Add(Form4->SelectedFactory->Caption + " за " + DateToStr(date1));

	 }
	 else {
		Form4->Chart3->Title->Text->Add("Оптимизированные данные по поставке товара для предприятия ");
		Form4->Chart3->Title->Text->Add(Form4->SelectedFactory->Caption + " за период с " + DateToStr(date1) + " по " + DateToStr(date2));
	 }





	for(int i=0; i < Form4->CheckListBox1->Count;i++){
		if(Form4->CheckListBox1->Checked[i]){



			Form4->Series1->AddBar(regions_was_values[i],regions->Strings[i], clYellow);
			Form4->Series2->AddBar(regions_values[i],regions->Strings[i],clBlue);
			//Form4->Series1->Add


		

			if(regions_was_values[i]>0)
				Form4->BarSeries2->AddPie(regions_was_values[i],regions->Strings[i]);

			if(regions_values[i]>0)
				Form4->PieSeries1->AddPie(regions_values[i],regions->Strings[i]);

		}


	}

}
void __fastcall TForm4::CheckListBox1ClickCheck(TObject *Sender)
{


    fillGrapgh();
}
//---------------------------------------------------------------------------




