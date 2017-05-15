#include <vcl.h>
#include <map>

class TabbedView : public TControl{

	TPanel *controller;
	TPanel *viewObject;
	static TabbedView* selectedTab;

	public:
	TabbedView(TPanel *c, TPanel *v, TForm *f) : TControl(f){

		controller = c;
		viewObject = v;
		controller->Cursor =crHandPoint;
		controller->OnClick = MyOnClickFunction;
	}

	void setSelected(){

		 controller->Font->Style = controller->Font->Style<<fsBold;
		 viewObject->Visible = true;
		 if(selectedTab!=NULL)
			selectedTab->unselectTab();
		 selectedTab = this;
	}
	void unselectTab(){
		  controller->Font->Style = controller->Font->Style>>fsBold;
		  viewObject->Visible = false;
	}

	static boolean isSelected(){
    	return selectedTab!=NULL;
	}


	void __fastcall MyOnClickFunction(TObject* Sender)
	{
		if(selectedTab!=this)
     		setSelected();
	};

	static void init(int pairsCount, TPanel* p, ...){


		va_list args;
		va_start(args, pairsCount);
		boolean isSelected = false;
		while(pairsCount--){

            TPanel *controller =  va_arg(args,TPanel*);
			TPanel *view = va_arg(args,TPanel*);



			TabbedView  * tv = (TabbedView*)new TabbedView(controller, view, Form1);
			if(!isSelected){
				tv->setSelected();
            	isSelected = true;
			}
			else
				tv->unselectTab();
		}

		va_end(args);

	}

};
TabbedView* TabbedView::selectedTab;
