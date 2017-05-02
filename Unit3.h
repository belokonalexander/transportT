//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
#include "Main.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>


#include "DBModels.h"


//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TValueListEditor *ValueListEditor1;
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *Button1;
	TButton *Button2;
	void __fastcall ValueListEditor1SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
	void setData(std::vector<Provider> *p);
	void setData(std::vector<Reciever> *r);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
