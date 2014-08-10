//
//  LIBSelectionObserver.cpp
//  Librelio
//
//  Created by Geert on 09/08/14.
//
//

#include "VCPlugInHeaders.h"
#include "LIBID.h"
#include "IGraphicAttributeSuite.h"
#include "IGraphicFrameData.h"
#include "IPanelControlData.h"
#include "ISelectionManager.h"
#include "SelectionObserver.h"
#include "CAlert.h"

class LIBSelectionObserver : public ActiveSelectionObserver
{
public:
    // Constructor
    LIBSelectionObserver(IPMUnknown *boss);
    
    // Methods
    virtual void AutoAttach();
    virtual void AutoDetach();
    virtual void HandleSelectionChanged(const ISelectionMessage *message);
    
    // Destructor
    virtual ~LIBSelectionObserver();
    
private:
    virtual void EnableWidget(const WidgetID& widgetID, bool16 enable);
};

CREATE_PMINTERFACE(LIBSelectionObserver, kLIBSelectionObserverImpl)

LIBSelectionObserver::LIBSelectionObserver(IPMUnknown *boss) : ActiveSelectionObserver(boss)
{
}

LIBSelectionObserver::~LIBSelectionObserver()
{
}

void LIBSelectionObserver::AutoAttach()
{
	// Call parent class so we attach the active selection.
	ActiveSelectionObserver::AutoAttach();
}

void LIBSelectionObserver::AutoDetach()
{
	// Call the parent class to detach from the active selection.
	ActiveSelectionObserver::AutoDetach();
}

void LIBSelectionObserver::EnableWidget(const WidgetID& widgetID, bool16 enable)
{
	do
	{
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());

		if (!panelData)
		{
			break;
		}
        
		IControlView* controlView = panelData->FindWidget(widgetID);
        
		if (!controlView)
		{
			break;
		}
        
		controlView->Enable(enable);
        
	} while(false);
}

void LIBSelectionObserver::HandleSelectionChanged(const ISelectionMessage* selectionMessage)
{
    bool16 enable = kFalse;

    InterfacePtr<IGraphicAttributeSuite> grSuite(fCurrentSelection, UseDefaultIID());
    
    if(grSuite != nil)
    {
        
        enable = kTrue;
    }
//    UIDRef itemUIDRef = fCurrentSelection->GetSelectionsOwner();
//    
//    if(itemUIDRef != nil)
//    {
//        InterfacePtr<IGraphicFrameData> graphicFrameData(/*itemUIDRef*/fCurrentSelection, UseDefaultIID());
//        
//        if(graphicFrameData != nil /*&& graphicFrameData->IsGraphicFrame()*/)
//        {
//            enable = kTrue;
//        }
//    }
    
    EnableWidget(kLIBTextBoxURLWidgetID, enable);
    EnableWidget(kLIBCheckBoxFullScreenWidgetID, enable);
    EnableWidget(kLIBCheckBoxAutoOpenWidgetID, enable);
}