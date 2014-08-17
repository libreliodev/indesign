//
//  LIBHyperlinkUtils.cpp
//  Librelio
//
//  Created by Geert on 16/08/14.
//
//

#include "LIBHyperlinkUtils.h"
#include "IHyperlink.h"
#include "IHyperlinkFacade.h"
#include "IHyperlinkDestination.h"
#include "IHyperlinkTable.h"
#include "CAlert.h"


LIBHyperlinkUtils::LIBHyperlinkUtils(const IDocument* pDocument)
{
    m_pDocument = pDocument;
}

LIBHyperlinkUtils::~LIBHyperlinkUtils()
{
}

ErrorCode LIBHyperlinkUtils::CreateHyperlink(const UIDRef& uidRef, const PMString& url, const UID sourceUID)
{
    ErrorCode result = kFailure;
    UIDRef sourceUIDRef;
    UIDRef destinationUIDRef;
    bool16 isExisting = kFalse;
    
    do
    {
        if(sourceUID == kInvalidUID)
        {
            // Create a new source
            result = Utils<Facade::IHyperlinkFacade>()->CreateHyperlinkPageItemSource(uidRef, &sourceUIDRef);
        }
        else
        {
            // Use existing source
            sourceUIDRef = UIDRef(uidRef.GetDataBase(), sourceUID);
            result = kSuccess;
            isExisting = kTrue;
        }
        
        if(result == kFailure || sourceUIDRef == nil)
        {
            break;
        }
        
        result = Utils<Facade::IHyperlinkFacade>()->CreateHyperlinkURLDestination(uidRef.GetDataBase(), url, &destinationUIDRef);
        
        if(result == kFailure || destinationUIDRef == nil)
        {
            break;
        }
        
        if(isExisting)
        {
            UIDRef hyperlinkUIDRef = this->GetHyperlinkUIDRef(sourceUIDRef);
            Utils<Facade::IHyperlinkFacade>()->ChangeDestinationForHyperlink(hyperlinkUIDRef, destinationUIDRef);
        }
        else
        {
            result = Utils<Facade::IHyperlinkFacade>()->CreateHyperlink(sourceUIDRef, destinationUIDRef);
        }
        
    } while (kFalse);
    
    return result;
}

UIDRef LIBHyperlinkUtils::GetHyperlinkUIDRef(const UIDRef sourceUIDRef)
{
    UIDRef hyperlinkUIDRef = kInvalidUIDRef;
    
    do
    {
        if(m_pDocument == nil || m_pDocument->GetDocWorkSpace() == nil || sourceUIDRef == nil)
        {
            break;
        }

        IDataBase* db = m_pDocument->GetDocWorkSpace().GetDataBase();
        
        if(db == nil)
        {
            break;
        }

        InterfacePtr<IHyperlinkTable> hyperlinkTable(m_pDocument, IID_IHYPERLINKTABLE);
        
        if(hyperlinkTable == nil)
        {
            break;
        }

        UID hyperlinkUID = hyperlinkTable->GetHyperlinkOfSource(sourceUIDRef);
        
        if(hyperlinkUID == kInvalidUID)
        {
            break;
        }
 
        hyperlinkUIDRef = UIDRef(db, hyperlinkUID);
        
    } while (kFalse);
    
    return hyperlinkUIDRef;
}

ErrorCode LIBHyperlinkUtils::GetHyperlink(const UID sourceUID, PMString& url)
{
    ErrorCode result = kFailure;
    
    do
    {
        IDataBase* db = m_pDocument->GetDocWorkSpace().GetDataBase();
        
        if(db == nil)
        {
            break;
        }

        UIDRef sourceUIDRef(db, sourceUID);
        
        if(sourceUIDRef == nil)
        {
            break;
        }

        UIDRef hyperlinkUIDRef = this->GetHyperlinkUIDRef(sourceUIDRef);
        InterfacePtr<IHyperlink> hyperlink(hyperlinkUIDRef, IID_IHYPERLINK);
        
        if(hyperlink == nil)
        {
            break;
        }

        UIDRef destinationUIDRef = hyperlink->GetDestinationUIDRef();
        InterfacePtr<IHyperlinkDestination> destination(destinationUIDRef, IID_IHYPERLINKDESTINATION);
        
        if(destination != nil)
        {
            destination->GetInfo(&url);
            result = kSuccess;
        }
        
    } while(kFalse);
    
    return result;
}