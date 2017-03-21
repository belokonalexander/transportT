#include "TabbedView.h"


	void TabbedView::setSelected(){

		 controller->Font->Style = controller->Font->Style<<fsBold;
		 viewObject->Visible = true;
		 if(selectedTab!=NULL)
			selectedTab->unselectTab();
		 selectedTab = this;
	}
	void TabbedView::unselectTab(){
		  controller->Font->Style = controller->Font->Style>>fsBold;
		  viewObject->Visible = false;
	}

	static boolean isSelected(){
    	return TabbedView::selectedTab!=NULL;
	}


	
};
TabbedView* TabbedView::selectedTab;
