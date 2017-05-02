#include <vcl.h>
#include <map>

class TabbedView2 : public TControl{

	TPanel *controller;
	TPanel *viewObject;
	static TabbedView2* selectedTab;

	public:
	TabbedView2(TPanel *c, TPanel *v, TForm *f) : TControl(f){

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



			TabbedView2  * tv = (TabbedView2*)new TabbedView2(controller, view, Form4);
			if(!isSelected){
				tv->setSelected();
            	isSelected = true;
			}
			else
				tv->unselectTab();
		}

		va_end(args);



		//for(int i =0; i < pairsCount; i++){
		//   TabbedView  * tv = (TabbedView*)new TabbedView(controller,viewObject, Form1);
		//}
		/*int count = Form1->Panel5->ControlCount;
		for(int i=0; i<count; i++){

		   TPanel *controller = (TPanel*)Form1->Panel5->Controls[i];
		   controller->Cursor = crHandPoint;
		   TPanel *viewObject;
		   boolean isSelected = false;
		   String number = controller->Name.SubString(6,controller->Name.Length());
		   if(number=="7"){
			viewObject = Form1->Panel10;
			isSelected = true;
		   } else if(number=="8"){
		   viewObject = Form1->Panel11;
		   } else if(number=="9"){
		   viewObject = Form1->Panel12;
		   }else if(number=="6"){
		   viewObject = Form1->Panel13;
		   }
		   TabbedView  * tv = (TabbedView*)new TabbedView(controller,viewObject, Form1);
		   if(isSelected)
				tv->setSelected();
			else
				tv->unselectTab();
	   }  */
	}

};
TabbedView2* TabbedView2::selectedTab;
