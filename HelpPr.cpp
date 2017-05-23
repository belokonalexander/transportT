//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HelpPr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THelpForm *HelpForm;
//---------------------------------------------------------------------------
__fastcall THelpForm::THelpForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THelpForm::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
RichEdit1->Clear();
if(Node->Text!="Справка")
 {
	RichEdit1->Lines->LoadFromFile("Help\\"+Node->Text+".rtf");
 }


}
//---------------------------------------------------------------------------
