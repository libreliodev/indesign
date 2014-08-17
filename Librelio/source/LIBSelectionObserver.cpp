//
//  LIBSelectionObserver.cpp
//  Librelio
//
//  Created by Geert on 09/08/14.
//
//

#include "VCPlugInHeaders.h"
#include "LIBID.h"
#include "ILIBSuite.h"
#include "SelectionObserver.h"
#include "CAlert.h"
#include "IDocument.h"
#include "IHyperlink.h"
#include "IHyperlinkDestination.h"
#include "IHyperlinkSuite.h"
#include "IHyperlinkTable.h"
#include "ILayoutUIUtils.h"
#include "IStringListControlData.h"
#include "ISelectionUtils.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "ISubject.h"
#include "ITextValue.h"
#include "ITriStateControlData.h"
#include "LIBStringUtils.h"

#include "LIBHyperlinkUtils.h"

class LIBSelectionObserver : public ActiveSelectionObserver
{
public:
    // Constructor
    LIBSelectionObserver(IPMUnknown *boss);
    
    // Methods
    virtual void AutoAttach();
    virtual void AutoDetach();
    
    // Destructor
    virtual ~LIBSelectionObserver();
    
protected:
    virtual void HandleSelectionChanged(const ISelectionMessage *message);
    virtual void HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
    
private:
    void AppendCheckboxValue(const IControlView* checkbox, const PMString& value);
    void AppendDropDownValue(const IControlView* checkbox, const PMString& value);
    void AppendUrl(const PMString& value, const bool16 append, const PMString& key = "");
    void AttachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);
    void DetachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);
    void EnableWidget(const WidgetID& widgetID, bool16 enable);
    void EnableWidgets(bool16 enable);
    IControlView* GetControl(const WidgetID& widgetID);
    bool16 GetCheckboxValue(const IControlView* checkbox);
    UID GetHyperlinkSource();
    void GetURLFromTextBox(PMString& url);
    void ParseUrl(const PMString& url);
    void ResetWidgets();
    void ResetCheckBoxes();
    void SetCheckBox(const WidgetID& widgetID, const bool16 check);
    void SetURLTextBoxValue(PMString url, bool16 notify);
    void URLWidgetValueChanged(IControlView* widgetControlView);
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
    
    // Observe the user changing the url widget value in the panel.
	InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());

	if(panelControlData)
	{
		this->AttachWidget(panelControlData, kLIBTextBoxURLWidgetID, ITextControlData::kDefaultIID);
        this->AttachWidget(panelControlData, kLIBCheckBoxAutoOpenWidgetID, ITriStateControlData::kDefaultIID);
        this->AttachWidget(panelControlData, kLIBCheckBoxFullScreenWidgetID, ITriStateControlData::kDefaultIID);
        this->AttachWidget(panelControlData, kLIBTransitionDropDownWidgetID, IStringListControlData::kDefaultIID);
        this->AttachWidget(panelControlData, kLIBBackgroundDropDownWidgetID, IStringListControlData::kDefaultIID);
        this->AttachWidget(panelControlData, kLIBTextBoxDelayWidgetID, ITextControlData::kDefaultIID);
	}
}

void LIBSelectionObserver::AutoDetach()
{
    // Stop observing the url widget.
	InterfacePtr<IPanelControlData> panelControlData(this, UseDefaultIID());

	if (panelControlData)
	{
		this->DetachWidget(panelControlData, kLIBTextBoxURLWidgetID, ITextControlData::kDefaultIID);
        this->DetachWidget(panelControlData, kLIBCheckBoxAutoOpenWidgetID, ITriStateControlData::kDefaultIID);
        this->DetachWidget(panelControlData, kLIBCheckBoxFullScreenWidgetID, ITriStateControlData::kDefaultIID);
        this->DetachWidget(panelControlData, kLIBTransitionDropDownWidgetID, IStringListControlData::kDefaultIID);
        this->DetachWidget(panelControlData, kLIBBackgroundDropDownWidgetID, IStringListControlData::kDefaultIID);
        this->DetachWidget(panelControlData, kLIBTextBoxDelayWidgetID, ITextControlData::kDefaultIID);
	}
    
	// Call the parent class to detach from the active selection.
	ActiveSelectionObserver::AutoDetach();
}

void LIBSelectionObserver::AttachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	do
	{
		IControlView* controlView = panelControlData->FindWidget(widgetID);

		if (controlView == nil)
		{
			break;
		}
        
		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());

		if (subject == nil)
		{
			break;
		}
        
		subject->AttachObserver(this, interfaceID, fObserverIID);
	}
	while (kFalse);
}

void LIBSelectionObserver::DetachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID)
{
	do
	{
		IControlView* controlView = panelControlData->FindWidget(widgetID);

		if (controlView == nil)
		{
			break;
		}
        
		InterfacePtr<ISubject> subject(controlView, UseDefaultIID());

		if (subject == nil)
		{
            break;
		}
        
		subject->DetachObserver(this, interfaceID, fObserverIID);
	}
	while (kFalse);
}

UID LIBSelectionObserver::GetHyperlinkSource()
{
    UID sourceUID = kInvalidUID;
    InterfacePtr<IHyperlinkSuite> hyperlinkSuite(fCurrentSelection, IID_IHYPERLINKSUITE);
    
    if(hyperlinkSuite != nil)
    {
        sourceUID = hyperlinkSuite->GetHyperlinkSource();
    }
    
    return sourceUID;
}

void LIBSelectionObserver::HandleSelectionChanged(const ISelectionMessage* selectionMessage)
{
    bool16 enable = kFalse;
    InterfacePtr<ILIBSuite> libSuite(fCurrentSelection, UseDefaultIID());
    
    if(libSuite != nil && libSuite->CanApplyLink())
    {
        enable = kTrue;
        
        do
        {
            ErrorCode result = kFailure;
            PMString url;
            UID sourceUID = this->GetHyperlinkSource();
            
            if(sourceUID != kInvalidUID)
            {
                IDocument* currentDocument = Utils<ILayoutUIUtils>()->GetFrontDocument();
                libSuite->GetLink(currentDocument, sourceUID, url);
            }
            
            IControlView* urlControl = this->GetControl(kLIBTextBoxURLWidgetID);
            
            if(urlControl == nil)
            {
                break;
            }
            
            InterfacePtr<ITextControlData> textValue(urlControl, UseDefaultIID());
            
            if (textValue == nil)
            {
                break;
            }
            
            if(url.IsEmpty() || url.IndexOfString("http") < 0)
            {
                url = "http://";
            }
            
            this->ParseUrl(url);
            
            // Do NOT notify observer
            textValue->SetString(url, kTrue, kFalse);
            
        } while(kFalse);
    }
    else
    {
        this->ResetWidgets();
    }
    
    this->EnableWidgets(enable);
}

void LIBSelectionObserver::HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	// Call the parent class to handle updates from the active selection.
	ActiveSelectionObserver::HandleSelectionUpdate(theChange, theSubject, protocol, changedBy);
    
	// Handle updates from the url widget on the panel.
	if (theChange == kTextChangeStateMessage ||
        theChange == kPopupChangeStateMessage ||
        theChange == kFalseStateMessage ||
        theChange == kTrueStateMessage)
	{
        
		InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
        
		if (controlView)
		{
			WidgetID widgetID = controlView->GetWidgetID();
            
			switch (widgetID.Get())
			{
				case kLIBTextBoxURLWidgetID:
                    
					this->URLWidgetValueChanged(controlView);
					break;
                    
                case kLIBCheckBoxAutoOpenWidgetID:
                    
                    this->AppendCheckboxValue(controlView, "waplay=auto");
                    break;
                    
                case kLIBCheckBoxFullScreenWidgetID:
                    
                    this->AppendCheckboxValue(controlView, "warect=full");
                    break;
                
                case kLIBTransitionDropDownWidgetID:
                    
//                    this->AppendDropDownValue(controlView, "watransition=");
                    break;
                    
                case kLIBBackgroundDropDownWidgetID:
                    
//                    this->AppendDropDownValue(controlView, "wabgcolor=");
                    break;
                    
                case kLIBTextBoxDelayWidgetID:
                    
//                    this->AppendTextBoxValue(controlView, "wadelay=");
                    break;
                    
				default:

					break;
			}
		}
	}
}

void LIBSelectionObserver::AppendCheckboxValue(const IControlView* checkbox, const PMString& value)
{
    bool16 append = this->GetCheckboxValue(checkbox);
    this->AppendUrl(value, append);
}

void LIBSelectionObserver::AppendDropDownValue(const IControlView* dropDown, const PMString& value)
{
    PMString finalValue = value;
    InterfacePtr<ITextControlData> dropDownValue(dropDown, UseDefaultIID());
    PMString result = PMString(dropDownValue->GetString());
    
    if(result == kLIBTransitionNoneKey)
    {
        result = "none";
    }
    else if(result == kLIBTransitionLeftToRightKey)
    {
        result = "movein";
    }
    else
    {
        result.Translate();
        result.ToLower();
    }
    
    finalValue.Append(result);
    this->AppendUrl(finalValue, kTrue, value);
}

void LIBSelectionObserver::AppendUrl(const PMString& value, const bool16 append, const PMString& key)
{
    bool16 dirty = kFalse;
    PMString url;
    this->GetURLFromTextBox(url);
    
    std::string str_url = url.GetPlatformString();
    std::string str_value = value.GetPlatformString();
    
    LIBStringUtils stringUtils;
    std::vector<std::string> parts = stringUtils.split(str_url, '?');
    std::string str_without = parts[0];
    
    if(parts.size() > 1)
    {
        bool16 notFound = kTrue;
        std::vector<std::string> args = stringUtils.split(parts[1], '&');
        
        if(args.size() > 0)
        {
            for(std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it)
            {
                if(!key.IsEmpty())
                {
                    if(it->find(key.GetPlatformString()) != std::string::npos)
                    {
                        args.erase(it);
                        dirty = kTrue;
                        break;
                    }
                }
                else if(it->compare(str_value)==0)
                {
                    if(!append)
                    {
                        args.erase(it);
                        dirty = kTrue;
                    }
                    
                    notFound = kFalse;
                    break;
                }
            }
        }
        
        if(dirty)
        {
            if(args.size() > 0)
            {
                str_without.append("?");
                
                for(int index = 0; index < args.size(); index++)
                {
                    str_without.append(args[index]);
                    
                    if(index < args.size() - 1)
                    {
                        str_without.append("&");
                    }
                }
            }
            
            str_url = str_without;
        }
        
        if(notFound && append)
        {
            str_url.append("&");
            str_url.append(str_value);
        }
    }
    else
    {
        if(append)
        {
            str_url.append("?");
            str_url.append(str_value);
        }
    }
    
    PMString newUrl = PMString(str_url.c_str());
    this->SetURLTextBoxValue(newUrl, kTrue);
    
}

void LIBSelectionObserver::EnableWidget(const WidgetID& widgetID, bool16 enable)
{
    IControlView* controlView = this->GetControl(widgetID);
    
    if(controlView != nil)
    {
        controlView->Enable(enable);
    }
}

void LIBSelectionObserver::EnableWidgets(bool16 enable)
{
    this->EnableWidget(kLIBTextBoxURLWidgetID, enable);
    this->EnableWidget(kLIBCheckBoxFullScreenWidgetID, enable);
    this->EnableWidget(kLIBCheckBoxAutoOpenWidgetID, enable);
    this->EnableWidget(kLIBBackgroundDropDownWidgetID, enable);
    this->EnableWidget(kLIBTransitionDropDownWidgetID, enable);
    this->EnableWidget(kLIBTextBoxDelayWidgetID, enable);
    
}

IControlView* LIBSelectionObserver::GetControl(const WidgetID& widgetID)
{
    IControlView* controlView = nil;
    InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
    
    if (panelData != nil)
    {
        controlView = panelData->FindWidget(widgetID);
    }
    
    return controlView;
}

bool16 LIBSelectionObserver::GetCheckboxValue(const IControlView* checkbox)
{
    bool16 selected = kFalse;
    
    if(checkbox != nil)
    {
        InterfacePtr<ITriStateControlData> checkValue(checkbox, UseDefaultIID());
        
        if(checkValue != nil)
        {
            selected = checkValue->IsSelected();
        }
    }
    
    return selected;
}

void LIBSelectionObserver::GetURLFromTextBox(PMString& url)
{
    IControlView* urlControl = this->GetControl(kLIBTextBoxURLWidgetID);
    InterfacePtr<ITextControlData> textValue(urlControl, UseDefaultIID());
    
    if (textValue != nil)
    {
        url = textValue->GetString();
    }
}

void LIBSelectionObserver::ParseUrl(const PMString &url)
{
    std::string str_url = url.GetPlatformString();

    LIBStringUtils stringUtils;
    std::vector<std::string> parts = stringUtils.split(str_url, '?');
    
    this->ResetCheckBoxes();
    
    if(parts.size() > 1)
    {
        std::vector<std::string> args = stringUtils.split(parts[1], '&');
        
        if(args.size() > 0)
        {
            // warect = full, waplay = auto
            for(std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it)
            {
                if(it->compare("warect=full")==0)
                {
                    this->SetCheckBox(kLIBCheckBoxFullScreenWidgetID, kTrue);
                }
                else if(it->compare("waplay=auto")==0)
                {
                    this->SetCheckBox(kLIBCheckBoxAutoOpenWidgetID, kTrue);
                }
            }
        }
    }
}

void LIBSelectionObserver::ResetCheckBoxes()
{
    this->SetCheckBox(kLIBCheckBoxAutoOpenWidgetID, kFalse);
    this->SetCheckBox(kLIBCheckBoxFullScreenWidgetID, kFalse);
}

void LIBSelectionObserver::ResetWidgets()
{
    do
    {
        IControlView* urlControl = this->GetControl(kLIBTextBoxURLWidgetID);
        
        if(urlControl == nil)
        {
            break;
        }
        
        InterfacePtr<ITextControlData> textValue(urlControl, UseDefaultIID());
            
        if(textValue != nil)
        {
            textValue->SetString("http://");
        }
        
        this->ResetCheckBoxes();
        
    } while(kFalse);
}

void LIBSelectionObserver::SetCheckBox(const WidgetID& widgetID, const bool16 check)
{
    IControlView* checkBox = this->GetControl(widgetID);
    
    do
    {
        if(checkBox == nil)
        {
            break;
        }
        
        InterfacePtr<ITriStateControlData> checkValue(checkBox, UseDefaultIID());
        
        if(checkValue == nil)
        {
            break;
        }
        
        if(check)
        {
            checkValue->Select(kTrue, kFalse);
        }
        else
        {
            checkValue->Deselect(kTrue, kFalse);
        }
        
    } while(kFalse);
}

void LIBSelectionObserver::SetURLTextBoxValue(PMString url, bool16 notify)
{
    IControlView* urlControl = this->GetControl(kLIBTextBoxURLWidgetID);
    InterfacePtr<ITextControlData> textValue(urlControl, UseDefaultIID());
    
    if (textValue != nil)
    {
        textValue->SetString(url, kTrue, notify);
    }
}

void LIBSelectionObserver::URLWidgetValueChanged(IControlView* widgetControlView)
{
	do
    {
        InterfacePtr<ILIBSuite> libSuite(fCurrentSelection, UseDefaultIID());
        
        if(libSuite == nil || !libSuite->CanApplyLink())
        {
            break;
        }
        
		InterfacePtr<ITextControlData> textValue(widgetControlView, UseDefaultIID());

		if (!textValue)
		{
			break;
		}
        
        PMString url = textValue->GetString();
        UID sourceUID = this->GetHyperlinkSource();
        IDocument* currentDocument = Utils<ILayoutUIUtils>()->GetFrontDocument();
        libSuite->ApplyLink(currentDocument, url, sourceUID);
        this->ParseUrl(url);
        
	} while(kFalse);
}