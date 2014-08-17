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

#include "VCPlugInHeaders.h"

// Interface includes:

// General includes:
#include "LIBSuiteCSB.h"

// Project includes:
#include "LIBID.h"

/** Check if a hyperlink can be applied to this selection
 @return kSucces when a hyperlink can be applied, kFalse otherwise
 */
bool16 LIBSuiteCSB::CanApplyLink(void)
{
    bool16 result = kFalse;
    UIDList items = GetTarget();
    
    if(items != nil && items.Length() == 1)
    {
        result = kTrue;
    }
    
    return result;
}

/** Performs apply link on the selection returning an ErrorCode.
 @return kSuccess on success, or an appropriate ErrorCode on failure. */
ErrorCode LIBSuiteCSB::ApplyLink(void)
{
    return kFailure;
}

