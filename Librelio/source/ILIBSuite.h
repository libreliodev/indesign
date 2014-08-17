//========================================================================================
//  
//  $File: $
//  
//  Owner: Kinanu
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ILIBSuite_h__
#define __ILIBSuite_h__

#include "IPMUnknown.h"
#include "LIBID.h"
#include "IDocument.h"

/** ILIBSuite defines the interface for this plug-ins selection suite.

    
    @ingroup librelio
*/
class ILIBSuite : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ILIBSUITE };

    /** Check if a hyperlink can be applied to this selection
     @return kSucces when a hyperlink can be applied, kFalse otherwise
     */
	virtual bool16 CanApplyLink(void) = 0;

	/** Performs apply link on the selection returning an ErrorCode.
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode ApplyLink(const IDocument* document, const PMString& url, const UID sourceUID) = 0;
    
    virtual ErrorCode GetLink(IDocument* document, UID sourceUID, PMString& url) = 0;
};
#endif // __ILIBSuite_h__
