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
#include "IDropDownListController.h"
#include "IDocument.h"
#include "IHyperlink.h"
#include "IHyperlinkDestination.h"
#include "IHyperlinkSuite.h"
#include "IHyperlinkTable.h"
#include "IMediaContent.h"
#include "IMediaSuite.h"
#include "ILayoutUIUtils.h"
#include "IStringListControlData.h"
#include "ISelectionUtils.h"
#include "IPanelControlData.h"
#include "ITextControlData.h"
#include "ISubject.h"
#include "ITextValue.h"
#include "ITriStateControlData.h"
#include "LIBHyperlinkUtils.h"
#include "URLParser.h"

#include <sstream>

class LIBSelectionObserver : public ActiveSelectionObserver
{
public:
    enum SelectionType
	{
		enNone,
        enObject,
		enMovie,
		enSlideshow,
	};
    
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
    virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
    
private:
    std::map<WidgetID, std::map<std::string, int32> > m_dropDownIndices;
    
    void AppendCheckboxValue(const IControlView* checkbox, const PMString& key, const PMString& value);
    void AppendDropDownValue(const IControlView* checkbox, const PMString& value);
    void AppendTextBoxValue(const IControlView* textBox, const PMString& key);
    void AppendUrl(const PMString& key, const PMString& value, const bool16 append);
    void AttachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);
    void DetachWidget(IPanelControlData* panelControlData, const WidgetID& widgetID, const PMIID& interfaceID);
    void EnableWidget(const WidgetID& widgetID, bool16 enable);
    void EnableWidgets(const SelectionType type);
    IControlView* GetControl(const WidgetID& widgetID);
    bool16 GetCheckboxValue(const IControlView* checkbox);
    int32 GetDropDownIndex(const WidgetID& widgetID, const std::string& value);
    UID GetHyperlinkSource();
    void GetValueFromTextBox(const WidgetID& widgetID, PMString& url);
    void ParseUrl(const PMString& url);
    void ResetWidgets();
    void ResetCheckBoxes();
    void SetCheckBox(const WidgetID& widgetID, const bool16 checked);
    void SetDropDown(const WidgetID& widgetID, const int32 index);
    void SetTextBoxValue(const WidgetID& widgetID, const PMString value, const bool16 notify);
    void URLWidgetValueChanged(IControlView* widgetControlView);
};

CREATE_PMINTERFACE(LIBSelectionObserver, kLIBSelectionObserverImpl)

LIBSelectionObserver::LIBSelectionObserver(IPMUnknown *boss) : ActiveSelectionObserver(boss)
{
    m_dropDownIndices[kLIBBackgroundDropDownWidgetID]["black"] = 0;
    m_dropDownIndices[kLIBBackgroundDropDownWidgetID]["white"] = 1;
    m_dropDownIndices[kLIBTransitionDropDownWidgetID]["none"] = 0;
    m_dropDownIndices[kLIBTransitionDropDownWidgetID]["movein"] = 1;
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
    SelectionType selectionType = enNone;
    
    InterfacePtr<ILIBSuite> libSuite(fCurrentSelection, UseDefaultIID());
    
    if(libSuite != nil && libSuite->CanApplyLink())
    {
        selectionType = enObject; //enSlideshow;
    }
    
    if(selectionType == enNone)
    {
        InterfacePtr<IMediaSuite> mediaSuite(fCurrentSelection, UseDefaultIID());
        
        if(mediaSuite != nil)
        {
            IMediaContent::MediaType type = mediaSuite->GetMediaType();
            
            if(type == IMediaContent::enLegacyVideo || type == IMediaContent::enVideo)
            {
                selectionType = enMovie;
            }
        }
    }
    
    if(selectionType != enNone)
    {
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
    
    this->EnableWidgets(selectionType);
}

void LIBSelectionObserver::HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	// Call the parent class to handle updates from the active selection.
	ActiveSelectionObserver::HandleSelectionUpdate(theChange, theSubject, protocol, changedBy);
    
    InterfacePtr<ILIBSuite> libSuite(fCurrentSelection, UseDefaultIID());
    
    if(libSuite != nil && libSuite->CanApplyLink())
    {
        // Handle updates from the url widget on the panel.
        if (theChange == kTextChangeStateMessage ||
            theChange == kPopupChangeStateMessage ||
            theChange == kFalseStateMessage ||
            theChange == kTrueStateMessage)
        {
            
            InterfacePtr<IControlView> controlView(theSubject, UseDefaultIID());
            
            if (controlView != nil)
            {
                WidgetID widgetID = controlView->GetWidgetID();
                
                switch (widgetID.Get())
                {
                    case kLIBTextBoxURLWidgetID:
                        
                        this->URLWidgetValueChanged(controlView);
                        break;
                        
                    case kLIBCheckBoxAutoOpenWidgetID:
                        

                        this->AppendCheckboxValue(controlView, "waplay", "auto");
                        break;
                        
                    case kLIBCheckBoxFullScreenWidgetID:
                        

                        this->AppendCheckboxValue(controlView, "warect", "full");
                        break;
                    
                    case kLIBTransitionDropDownWidgetID:


                      this->AppendDropDownValue(controlView, "watransition");
                        break;
                        
                    case kLIBBackgroundDropDownWidgetID:
                        

                        this->AppendDropDownValue(controlView, "wabgcolor");
                        break;
                        
                    case kLIBTextBoxDelayWidgetID:
                        

                        this->AppendTextBoxValue(controlView, "wadelay");
                        break;
                        
                    default:

                        break;
                }
            }
        }
    }
}

void LIBSelectionObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
    ActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);
}

void LIBSelectionObserver::AppendCheckboxValue(const IControlView* checkbox, const PMString& key, const PMString& value)
{
    bool16 append = this->GetCheckboxValue(checkbox);
    this->AppendUrl(key, value, append);
}

void LIBSelectionObserver::AppendDropDownValue(const IControlView* dropDown, const PMString& key)
{
    bool16 append = kTrue;
    InterfacePtr<ITextControlData> dropDownValue(dropDown, UseDefaultIID());
    PMString value = PMString(dropDownValue->GetString());
    
    if(value == kLIBTransitionNoneKey)
    {
        value = "none";
        append = kFalse;
    }
    else if(value == kLIBTransitionLeftToRightKey)
    {
        value = "movein";
    }
    else
    {
        value.Translate();
        value.ToLower();
        
        if(value == "black")
        {
            append = kFalse;
        }
    }
    
    this->AppendUrl(key, value, append);
}

void LIBSelectionObserver::AppendTextBoxValue(const IControlView* textBox, const PMString& key)
{
    bool16 append = kTrue;
    PMString value;
    this->GetValueFromTextBox(textBox->GetWidgetID(), value);
    
    if(value == "0")
    {
        append = kFalse;
    }
    
    this->AppendUrl(key, value, append);
}

void LIBSelectionObserver::AppendUrl(const PMString& key, const PMString& value, const bool16 append)
{
    PMString url;
    this->GetValueFromTextBox(kLIBTextBoxURLWidgetID, url);
    
    std::string str_url = url.GetUTF8String();
    std::string str_key = key.GetUTF8String();
    std::string str_value = value.GetUTF8String();
    
    URLParser urlParser;
    urlParser.parse(str_url);
    
    if(append)
    {
        urlParser.add(str_key, str_value);
    }
    else
    {
        urlParser.remove(str_key);
    }
    
    str_url = urlParser.getURL();
    PMString newUrl = PMString(str_url.c_str());
    this->SetTextBoxValue(kLIBTextBoxURLWidgetID, newUrl, kTrue);
}

void LIBSelectionObserver::EnableWidget(const WidgetID& widgetID, bool16 enable)
{
    IControlView* controlView = this->GetControl(widgetID);
    
    if(controlView != nil)
    {
        controlView->Enable(enable);
    }
}

void LIBSelectionObserver::EnableWidgets(SelectionType type)
{
    bool16 enable = kFalse;
    
    if(type == enMovie || type == enSlideshow || type == enObject)
    {
        enable = kTrue;
    }
    
    this->EnableWidget(kLIBTextBoxURLWidgetID, enable);
    this->EnableWidget(kLIBCheckBoxFullScreenWidgetID, enable);
    this->EnableWidget(kLIBCheckBoxAutoOpenWidgetID, enable);
    
    if(type == enMovie)
    {
        enable = kFalse;
    }
    
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

int32 LIBSelectionObserver::GetDropDownIndex(const WidgetID& widgetID, const std::string& value)
{
    return m_dropDownIndices[widgetID][value];
}

void LIBSelectionObserver::GetValueFromTextBox(const WidgetID& widgetID, PMString& value)
{
    IControlView* urlControl = this->GetControl(widgetID);
    InterfacePtr<ITextControlData> textValue(urlControl, UseDefaultIID());
    
    if (textValue != nil)
    {
        value = textValue->GetString();
    }
}

void LIBSelectionObserver::ParseUrl(const PMString &url)
{
    std::string str_url = url.GetUTF8String();
    URLParser urlParser;
    
    urlParser.parse(str_url);
    std::string fullscreen = urlParser.getArgValue("warect");
    std::string autoPlay = urlParser.getArgValue("waplay");
    std::string transition = urlParser.getArgValue("watransition", "None");
    std::string background = urlParser.getArgValue("wabgcolor", "Black");
    PMString delay = PMString(urlParser.getArgValue("wadelay", "0").c_str());
    
    this->SetCheckBox(kLIBCheckBoxFullScreenWidgetID, !fullscreen.empty());
    this->SetCheckBox(kLIBCheckBoxAutoOpenWidgetID, !autoPlay.empty());
    this->SetDropDown(kLIBTransitionDropDownWidgetID, this->GetDropDownIndex(kLIBTransitionDropDownWidgetID, transition));
    this->SetDropDown(kLIBBackgroundDropDownWidgetID, this->GetDropDownIndex(kLIBBackgroundDropDownWidgetID, background));
    this->SetTextBoxValue(kLIBTextBoxDelayWidgetID, delay, kFalse);
}

void LIBSelectionObserver::ResetCheckBoxes()
{
    this->SetCheckBox(kLIBCheckBoxAutoOpenWidgetID, kFalse);
    this->SetCheckBox(kLIBCheckBoxFullScreenWidgetID, kFalse);
    this->SetDropDown(kLIBTransitionDropDownWidgetID, 0);
    this->SetDropDown(kLIBBackgroundDropDownWidgetID, 0);
    this->SetTextBoxValue(kLIBTextBoxDelayWidgetID, "0", kFalse);
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

void LIBSelectionObserver::SetCheckBox(const WidgetID& widgetID, const bool16 checked)
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
        
        if(checked)
        {
            checkValue->Select(kTrue, kFalse);
        }
        else
        {
            checkValue->Deselect(kTrue, kFalse);
        }
        
    } while(kFalse);
}

void LIBSelectionObserver::SetDropDown(const WidgetID& widgetID, const int32 index)
{
    IControlView* dropDown = this->GetControl(widgetID);
    InterfacePtr<IDropDownListController> dropDownController(dropDown, UseDefaultIID());
    
    if(dropDownController != nil)
    {
        dropDownController->Select(index, kTrue, kFalse);
    }
}

void LIBSelectionObserver::SetTextBoxValue(const WidgetID& widgetID, const PMString value, const bool16 notify)
{
    IControlView* textBox = this->GetControl(widgetID);
    InterfacePtr<ITextControlData> textValue(textBox, UseDefaultIID());
    
    if (textValue != nil)
    {
        textValue->SetString(value, kTrue, notify);
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