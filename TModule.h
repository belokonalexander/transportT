//---------------------------------------------------------------------------

#ifndef TModuleH
#define TModuleH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>


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
	TButton *ButtonStart;
	TMemo *MemoInfo;
	void __fastcall ButtonStartClick(TObject *Sender);
private:	// User declarations
	String caption;
public:		// User declarations
	__fastcall TTModuleForm(TComponent* Owner);
	void setData(const std::vector<Provider> *p, const std::vector<Reciever> *r, const std::vector<Tarif> *t, const std::vector<Result> *res);

};
//---------------------------------------------------------------------------
extern PACKAGE TTModuleForm *TModuleForm;
//---------------------------------------------------------------------------
#endif

//std::vector<Provider> providers;
//	std::vector<Reciever> recievers;
//	std::vector<Tarif> tarifs;
//	std::vector<Result> results;