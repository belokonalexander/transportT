//---------------------------------------------------------------------------

#ifndef TReportH
#define TReportH
#include "Main.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdCtrls.hpp>
 #include <vector>
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TStringGrid *StringGrid1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
    void setData(String reportName);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
