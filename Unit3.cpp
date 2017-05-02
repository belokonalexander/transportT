//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

boolean recieverMode = false;
boolean providerMode = false;

std::vector<Reciever> r_s;
std::vector<Provider> p_s;



void init();

void TForm3::setData(std::vector<Reciever> *r){

	  init();

	  Form3->Caption = "Редактирование данных потребителей";

	    TStringList * strings1 = new TStringList;
		strings1->Add("Завод-потребитель");
		strings1->Add("Ед. продукции");

		for(int i =0; i < r->size(); i++){

			if(r->at(i).factory_id>0) {
			  r_s.push_back(r->at(i));
			  Form3->ValueListEditor1->InsertRow(r->at(i).factory_str,r->at(i).needs, true);
			}


		}


	

	   Form3->ValueListEditor1->TitleCaptions= strings1;



	recieverMode = true;
	providerMode = false;

}

void TForm3::setData(std::vector<Provider> *p){
	  //reportName = r;


	  init();

	  Form3->Caption = "Редактирование данных поставщиков";

	  TStringList * strings1 = new TStringList;
	  strings1->Add("Завод-поставщик");
	  strings1->Add("Ед. продукции");

	  Form3->ValueListEditor1->TitleCaptions= strings1;

	  recieverMode = false;
	  providerMode = true;

}

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm3::ValueListEditor1SetEditText(TObject *Sender, int ACol, int ARow,
		  const UnicodeString Value)
{
	static recursionUpdate = false;
	if(!recursionUpdate && recieverMode) {
        try {
		int val = StrToInt(Value);
		if( r_s[ARow-1].needs!=val) {
			r_s[ARow-1].needs = val;
					//Form3->Memo1->Lines->Add(IntToStr(r_s[ARow-1].needs)) ;
		}
		} catch (...) {
				recursionUpdate = true;
				if(Value=="") {
                   Form3->ValueListEditor1->Cells[ACol][ARow] = 0;
				} else {
					Form3->ValueListEditor1->Cells[ACol][ARow] = r_s[ARow-1].needs;
				}
		}
	}

	recursionUpdate = false;






}
//---------------------------------------------------------------------------

void init(){

	recieverMode = false;
	providerMode = false;

    r_s.clear();
	p_s.clear();

	  TStringList * strings1 = new TStringList;
	  Form3->ValueListEditor1->Strings = strings1;

	//Form3->Memo1->Lines->Add(Form3->ValueListEditor1->Strings->Text);

	//while (Form3->ValueListEditor1->RowCount > 2)
	  //Form3->ValueListEditor1->DeleteRow(1);



}
void __fastcall TForm3::Button1Click(TObject *Sender)
{
	Form1->updateRecievers(&r_s);
	Form3->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
   Form3->Close();
}
//---------------------------------------------------------------------------

