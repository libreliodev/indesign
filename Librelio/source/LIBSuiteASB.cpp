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
#include "ILIBSuite.h"

// General includes:
#include "SelectionASBTemplates.tpp"
#include "K2Vector.tpp"

// Project includes:
#include "LIBID.h"


/** Provides the ASB implementation for the plug-ins selection suite.

    
    @ingroup librelio
*/
class LIBSuiteASB : public CPMUnknown<ILIBSuite>
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	LIBSuiteASB(IPMUnknown* boss) : CPMUnknown<ILIBSuite>(boss) {};

	/** Destructor. Does nothing.
	*/
	~LIBSuiteASB() {}

    /** Check if a hyperlink can be applied to this selection
     @return kSucces when a hyperlink can be applied, kFalse otherwise
     */
	virtual bool16 CanApplyLink(void);
    
	/** Performs apply link on the selection returning an ErrorCode.
     @return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode ApplyLink(void);
    
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(LIBSuiteASB, kLIBSuiteASBImpl)

bool16 LIBSuiteASB::CanApplyLink(void)
{
	return( AnyCSBSupports(make_functor(&ILIBSuite::CanApplyLink), this, IID_ILIBSUITE));
}

ErrorCode LIBSuiteASB::ApplyLink(void)
{
	return( Process(make_functor(&ILIBSuite::ApplyLink), this, IID_ILIBSUITE));
}