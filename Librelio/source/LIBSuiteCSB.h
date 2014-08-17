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

#pragma once
#ifndef __LIBSuiteCSB_h__
#define __LIBSuiteCSB_h__

#include "IPMUnknown.h"
#include "ILIBSuite.h"
#include "LIBID.h"
#include "UIDList.h"

/**  This class can be used to implement code common to all ILIBSuite CSBs.
       For example, you may be calling the same code in each CSB, you just find the UIDs to operate on differently.
*/
class LIBSuiteCSB : public CPMUnknown<ILIBSuite>
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	LIBSuiteCSB(IPMUnknown* boss) : CPMUnknown<ILIBSuite>(boss) {};

	/** Destructor. Does nothing.
	*/
	~LIBSuiteCSB() {}

    /** Check if a hyperlink can be applied to this selection
     @return kSucces when a hyperlink can be applied, kFalse otherwise
     */
	virtual bool16 CanApplyLink(void);
    
	/** Performs apply link on the selection returning an ErrorCode.
     @return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode ApplyLink(void);

protected:
    virtual UIDList GetTarget(void);
};
#endif // LIBSuiteCSB_h__
