//---------------------------------------------------------------------------

#ifndef HelpPrH
#define HelpPrH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class THelpForm : public TForm
{
__published:	// IDE-managed Components
	TTreeView *TreeView1;
	TPanel *Panel1;
	TRichEdit *RichEdit1;
	void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);

private:	// User declarations
public:		// User declarations
	__fastcall THelpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THelpForm *HelpForm;
//---------------------------------------------------------------------------
#endif
