//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TReport.h"
#include "DBModels.h"
#include "Helper.h"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}

String reportName;

std::vector<ReportSummary> summary;
//---------------------------------------------------------------------------

void TForm2::setData(String r){

	  reportName = r;
}

std::vector<int> coloured;
std::vector<int> row;

void __fastcall TForm2::FormActivate(TObject *Sender)
{
	/*TFDQuery *query;
	query = new TFDQuery(NULL);

	query->Connection = Form1->TransportdbConnection;

	query->SQL->Text = "SELECT * FROM getSummary('" + reportName + "')";
	query->Open();

	int count = 0;

		while (!query->Eof) {

		count =   query-> FieldByName("id")->AsInteger;

		Memo1->Lines->Add(count);

		query->Next();

	}

	query->Close();
	query->Disconnect();
	*/

	


}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
	TStringList * title = new TStringList;
		title->Add("Свойство");
		title->Add("Исходные данные");
		title->Add("Данные после обработки");

	StringGrid1->Rows[0] = title;
	StringGrid1->ColWidths[0] = 342;
	StringGrid1->ColWidths[1] = 342;
	StringGrid1->ColWidths[2] = 342;

	StringGrid1->Cells[0][1] = "Общие затраты, рубли";
	StringGrid1->Cells[0][2] = "Ед.продукции, тонны";
	StringGrid1->Cells[0][3] = "Самый активный маршрут (тонны)";
	StringGrid1->Cells[0][4] = "Самый дорогой маршрут (тонны)";



	StringGrid1->Cells[0][6] = "Маршруты / eд.продукции, тонны";


	int offset = 7;

	StringGrid1->RowCount = 6;

	TFDQuery *query;
	query = new TFDQuery(NULL);

	query->Connection = Form1->TransportdbConnection;

	query->SQL->Text = "SELECT * FROM getSummary('" + reportName + "') ORDER BY provider";
	query->Open();

	double sum1=0;
	double sum2 =0 ;

	long sum1_prod=0;
	long sum2_prod=0 ;

	int act1 = 0;
	int act2 = 0;
	int act1_m = 0;
	int act2_m = 0;

	int cost1 = 0;
	int cost2 = 0;
	double cost1_m = 0;
	double cost2_m = 0;

	int count = 0;
	int ord = 0;

	int was_station_p = 0;
	int now_station_p = 0;

	summary.clear();
	coloured.clear();
    row.clear();

		while (!query->Eof) {

		count =   query-> FieldByName("id")->AsInteger;

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
		//самый популярный маршрут
		if(act1_m < rs->was_value) {
		   act1_m = rs->was_value;
		   act1 = rs->id;
		}

		if(act2_m < rs->value) {
		   act2_m = rs->value;
		   act2 = rs->id;
		}


		//самый дорогой маршрут
		if(cost1_m < rs->was_value * rs->cost) {
		   cost1_m = rs->was_value * rs->cost;
		   cost1 = rs->id;
		}

		if(cost2_m < rs->value * rs->cost) {
		   cost2_m = rs->value * rs->cost;
		   cost2 = rs->id;
		}


		sum2+= rs->value * rs->cost;
		sum1+= rs->was_value * rs->cost;

		sum1_prod+=rs->was_value;
		sum2_prod+=rs->value;

		summary.push_back(*rs);



		if(ord==0) {
			   was_station_p+=summary[ord].was_value;
			   now_station_p+=summary[ord].was_value;
		} else
			if(summary[ord].provider_id!=summary[ord-1].provider_id){



				StringGrid1->RowCount = offset+1;



				StringGrid1->Cells[0][offset] =  "ИТОГО: " +summary[ord-1].station_provider;
				StringGrid1->Cells[1][offset] =  was_station_p;
				StringGrid1->Cells[2][offset] =  now_station_p;



				if(was_station_p!=now_station_p) {
                  coloured.push_back(offset);
				}

				row.push_back(offset);

				was_station_p = summary[ord].was_value;
				now_station_p = summary[ord].value;



				offset++;

			} else {
			   was_station_p+=summary[ord].was_value;
			   now_station_p+=summary[ord].value;
			}

		StringGrid1->RowCount = offset+1;

		StringGrid1->Cells[0][offset] = rs->station_provider + " -> " + rs-> station_reciever;
		StringGrid1->Cells[1][offset] =  rs->was_value;
		StringGrid1->Cells[2][offset] =  rs->value;

		offset++;



		ord++;

		query->Next();

	}

		StringGrid1->RowCount = offset+1;
        if(was_station_p!=now_station_p) {
		   coloured.push_back(offset);
		}
        row.push_back(offset);
		StringGrid1->Cells[0][offset] =  "ИТОГО: " +summary[ord-1].station_provider;
		StringGrid1->Cells[1][offset] =  was_station_p;
		StringGrid1->Cells[2][offset] =  now_station_p;
		offset++;



		StringGrid1->Cells[1][1] = roundA(sum1);
		StringGrid1->Cells[2][1] = roundA(sum2);;

		StringGrid1->Cells[1][2] = sum1_prod;
		StringGrid1->Cells[2][2] = sum2_prod;

		for( int i =0; i < summary.size(); i++){

			if(summary[i].id == act1) {
				StringGrid1->Cells[1][3] = summary[i].station_provider + " -> " + summary[i].station_reciever + " (" + summary[i].was_value + ")";
			}

			if(summary[i].id == act2) {
				StringGrid1->Cells[2][3] = summary[i].station_provider + " -> " + summary[i].station_reciever + " (" + summary[i].value + ")";
			}




			if(summary[i].id == cost1) {
				StringGrid1->Cells[1][4] = summary[i].station_provider + " -> " + summary[i].station_reciever + " (" + summary[i].was_value*summary[i].cost + ")";
			}

			if(summary[i].id == cost2) {
				StringGrid1->Cells[2][4] = summary[i].station_provider + " -> " + summary[i].station_reciever + " (" + summary[i].value*summary[i].cost + ")";
			}

		}


	query->Close();
	query->Disconnect();
}


//---------------------------------------------------------------------------
void __fastcall TForm2::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{

	//Memo1->Lines->Add(" ---> " + IntToStr(ARow)+ " / " + IntToStr(lastRow));

 if (ARow != 0 && std::find(row.begin(),row.end(), ARow) != row.end()) {


		StringGrid1->Canvas->Brush->Color = clSilver;
		StringGrid1->Canvas->FillRect(Rect);

		if(ACol!=0) {
			if(std::find(coloured.begin(),coloured.end(), ARow) != coloured.end())
				StringGrid1->Canvas->Font->Color = clRed;
			else StringGrid1->Canvas->Font->Color = clGreen;

			StringGrid1->Canvas->Font->Style = StringGrid1->Canvas->Font->Style << fsBold;
			StringGrid1->Canvas->TextOut(Rect.Left+2, Rect.Top+2, StringGrid1->Cells[ACol][ARow]);
		} else {
			StringGrid1->Canvas->Font->Color = clBlack;
            StringGrid1->Canvas->Font->Style = StringGrid1->Canvas->Font->Style << fsBold;
			StringGrid1->Canvas->TextOut(Rect.Left+22, Rect.Top+2, StringGrid1->Cells[ACol][ARow]);
        }
    }
}
//---------------------------------------------------------------------------

