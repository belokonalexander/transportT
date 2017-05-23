//---------------------------------------------------------------------------

#ifndef TModuleH
#define TModuleH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include "Main.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>

#include <vector>


#include "DBModels.h"

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TTModuleForm : public TForm
{
__published:	// IDE-managed Components
	TMemo *MemoInfo;
	TPanel *Panel1;
	TPanel *Panel2;
	TProgressBar *ProgressBar1;
	TPanel *Panel3;
	TLabel *ReportExists;
	TPanel *Panel4;
	TPanel *Panel5;
	TStringGrid *StringGrid1;
	TLabel *Label1;
	TLabel *ReportName;
	TLabel *Label2;
	TLabel *TotalSum;
	TComboBox *ComboBox1;
	TSpeedButton *ReportRecieversButton;
	TSpeedButton *ReportButton;
	TSpeedButton *Button1;
	TSpeedButton *ButtonStart;
	void __fastcall ButtonStartClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ReportButtonClick(TObject *Sender);
	void __fastcall ReportRecieversButtonClick(TObject *Sender);
private:	// User declarations
	String caption;
public:		// User declarations
	__fastcall TTModuleForm(TComponent* Owner);
	void setData(const String reportName, const std::vector<Provider> *p, const std::vector<Reciever> *r, const std::vector<Tarif> *t, const std::vector<Result> *res);

};
//---------------------------------------------------------------------------
extern PACKAGE TTModuleForm *TModuleForm;
//---------------------------------------------------------------------------
#endif

//std::vector<Provider> providers;
//	std::vector<Reciever> recievers;
//	std::vector<Tarif> tarifs;
//	std::vector<Result> results;