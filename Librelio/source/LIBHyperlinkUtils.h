//
//  HyperlinkUtils.h
//  Librelio
//
//  Created by Geert on 16/08/14.
//
//

#ifndef __Librelio__HyperlinkUtils__
#define __Librelio__HyperlinkUtils__

#include "VCPlugInHeaders.h"
#include "IDocument.h"

class LIBHyperlinkUtils
{
public:
    LIBHyperlinkUtils(const IDocument* document);
    ~LIBHyperlinkUtils();
    ErrorCode CreateHyperlink(const UIDRef& uidRef, const PMString& url, const UID sourceUID);
    ErrorCode GetHyperlink(const UID sourceUID, PMString& url);
    
private:
    const IDocument* m_pDocument;
    UIDRef GetHyperlinkUIDRef(const UIDRef sourceUIDRef);
};

#endif /* defined(__Librelio__HyperlinkUtils__) */
