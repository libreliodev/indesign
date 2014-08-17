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
#include "UIDList.h"


/** LIBSuiteDefaultsCSB is the defaults specific implementation of LIBSuiteCSB.

    
    @ingroup librelio
*/
class LIBSuiteDefaultsCSB : public LIBSuiteCSB
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	LIBSuiteDefaultsCSB(IPMUnknown* boss) : LIBSuiteCSB(boss) {};

	/** Destructor. Does nothing.
	*/
	~LIBSuiteDefaultsCSB() {}

	//
	// Add any defaults specific implementations here
	//
protected:
    virtual UIDList GetTarget(void);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(LIBSuiteDefaultsCSB, kLIBSuiteDefaultsCSBImpl)

//
// Add any defaults specific implementations here
//
UIDList LIBSuiteDefaultsCSB::GetTarget(void)
{
    return nil;
}