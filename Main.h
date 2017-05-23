//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.MSSQL.hpp>
#include <FireDAC.Phys.MSSQLDef.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <Vcl.Buttons.hpp>


#include <vector>


#include "DBModels.h"



//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TPanel *Panel4;
	TEdit *Edit8;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TPanel *Panel12;
	TPanel *Panel13;
	TFDConnection *TransportdbConnection;
	TMemo *Memo1;
	TStringGrid *ProvidersGrid;
	TPanel *Panel14;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *ProvidersCount;
	TLabel *ReserveCount;
	TPanel *Panel15;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *RecieversCount;
	TLabel *NeedsCount;
	TStringGrid *RecieversGrid;
	TStringGrid *TarifsGrid;
	TStringGrid *ResultsGrid;
	TPanel *Panel16;
	TLabel *Label7;
	TLabel *ResultCost;
	TComboBox *ComboBox1;
	TLabel *Label9;
	TPanel *Panel17;
	TLabel *Label8;
	TLabel *Label10;
	TSpeedButton *ExecuteButton;
	TSpeedButton *Button1;
	TEdit *Edit6;
	TSpeedButton *Button2;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ExecuteButtonClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall ComboBox1DropDown(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void updateRecievers(std::vector<Reciever> *r);
	void updateProviders(std::vector<Provider> *p);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
