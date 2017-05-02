//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "DBModels.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.CheckLst.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <vector>
#include "TReport.h"

//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TListBox *ListBox1;
	TPanel *Panel2;
	TLabel *SelectedFactory;
	TMemo *Memo1;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *Panel9;
	TCheckListBox *CheckListBox1;
	TScrollBox *ScrollBox1;
	TChart *Chart1;
	TBarSeries *Series1;
	TBarSeries *Series2;

	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall CheckListBox1ClickCheck(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
    void setData(String reportName);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
