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
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#ifndef __LIBID_h__
#define __LIBID_h__

#include "SDKDef.h"

// Company:
#define kLIBCompanyKey	kSDKDefPlugInCompanyKey		// Company name used internally for menu paths and the like. Must be globally unique, only A-Z, 0-9, space and "_".
#define kLIBCompanyValue	kSDKDefPlugInCompanyValue	// Company name displayed externally.

// Plug-in:
#define kLIBPluginName	"Librelio"			// Name of this plug-in.
#define kLIBPrefixNumber	0xe9400 		// Unique prefix number for this plug-in(*Must* be obtained from Adobe Developer Support).
#define kLIBVersion		kSDKDefPluginVersionString						// Version of this plug-in (for the About Box).
#define kLIBAuthor		"Kinanu"					// Author of this plug-in (for the About Box).

// Plug-in Prefix: (please change kLIBPrefixNumber above to modify the prefix.)
#define kLIBPrefix		RezLong(kLIBPrefixNumber)				// The unique numeric prefix for all object model IDs for this plug-in.
#define kLIBStringPrefix	SDK_DEF_STRINGIZE(kLIBPrefixNumber)	// The string equivalent of the unique prefix number for  this plug-in.

// Missing plug-in: (see ExtraPluginInfo resource)
#define kLIBMissingPluginURLValue		kSDKDefPartnersStandardValue_enUS // URL displayed in Missing Plug-in dialog
#define kLIBMissingPluginAlertValue	kSDKDefMissingPluginAlertValue // Message displayed in Missing Plug-in dialog - provide a string that instructs user how to solve their missing plug-in problem

// PluginID:
DECLARE_PMID(kPlugInIDSpace, kLIBPluginID, kLIBPrefix + 0)

// ClassIDs:
DECLARE_PMID(kClassIDSpace, kLIBActionComponentBoss, kLIBPrefix + 0)
DECLARE_PMID(kClassIDSpace, kLIBPanelWidgetBoss, kLIBPrefix + 1)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 3)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 4)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 5)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 6)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 7)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 8)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 9)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 10)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 11)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 12)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 13)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 14)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 15)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 16)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 17)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 18)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 19)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 20)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 21)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 22)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 23)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 24)
//DECLARE_PMID(kClassIDSpace, kLIBBoss, kLIBPrefix + 25)


// InterfaceIDs:
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 0)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 1)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 2)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 3)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 4)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 5)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 6)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 7)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 8)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 9)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 10)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 11)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 12)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 13)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 14)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 15)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 16)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 17)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 18)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 19)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 20)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 21)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 22)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 23)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 24)
//DECLARE_PMID(kInterfaceIDSpace, IID_ILIBINTERFACE, kLIBPrefix + 25)


// ImplementationIDs:
DECLARE_PMID(kImplementationIDSpace, kLIBActionComponentImpl, kLIBPrefix + 0 )
DECLARE_PMID(kImplementationIDSpace, kLIBSelectionObserverImpl, kLIBPrefix + 1)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 2)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 3)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 4)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 5)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 6)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 7)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 8)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 9)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 10)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 11)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 12)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 13)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 14)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 15)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 16)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 17)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 18)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 19)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 20)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 21)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 22)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 23)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 24)
//DECLARE_PMID(kImplementationIDSpace, kLIBImpl, kLIBPrefix + 25)


// ActionIDs:
DECLARE_PMID(kActionIDSpace, kLIBAboutActionID, kLIBPrefix + 0)
DECLARE_PMID(kActionIDSpace, kLIBPanelWidgetActionID, kLIBPrefix + 1)
DECLARE_PMID(kActionIDSpace, kLIBSeparator1ActionID, kLIBPrefix + 2)
DECLARE_PMID(kActionIDSpace, kLIBPopupAboutThisActionID, kLIBPrefix + 3)//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 5)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 6)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 7)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 8)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 9)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 10)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 11)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 12)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 13)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 14)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 15)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 16)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 17)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 18)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 19)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 20)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 21)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 22)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 23)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 24)
//DECLARE_PMID(kActionIDSpace, kLIBActionID, kLIBPrefix + 25)


// WidgetIDs:
DECLARE_PMID(kWidgetIDSpace, kLIBPanelWidgetID, kLIBPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kLIBLabelURLWidgetID, kLIBPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kLIBTextBoxURLWidgetID, kLIBPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kLIBCheckBoxFullScreenWidgetID, kLIBPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kLIBCheckBoxAutoOpenWidgetID, kLIBPrefix + 4)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 5)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 6)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 7)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 8)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 9)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 10)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 11)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 12)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 13)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 14)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 15)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 16)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 17)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 18)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 19)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 20)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 21)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 22)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 23)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 24)
//DECLARE_PMID(kWidgetIDSpace, kLIBWidgetID, kLIBPrefix + 25)


// "About Plug-ins" sub-menu:
#define kLIBAboutMenuKey			kLIBStringPrefix "kLIBAboutMenuKey"
#define kLIBAboutMenuPath		kSDKDefStandardAboutMenuPath kLIBCompanyKey

// "Plug-ins" sub-menu:
#define kLIBPluginsMenuKey 		kLIBStringPrefix "kLIBPluginsMenuKey"
#define kLIBPluginsMenuPath		kSDKDefPlugInsStandardMenuPath kLIBCompanyKey kSDKDefDelimitMenuPath kLIBPluginsMenuKey

// Menu item keys:

// Other StringKeys:
#define kLIBAboutBoxStringKey	kLIBStringPrefix "kLIBAboutBoxStringKey"
#define kLIBPanelTitleKey					kLIBStringPrefix	"kLIBPanelTitleKey"
#define kLIBStaticTextKey kLIBStringPrefix	"kLIBStaticTextKey"
#define kLIBInternalPopupMenuNameKey kLIBStringPrefix	"kLIBInternalPopupMenuNameKey"
#define kLIBTargetMenuPath kLIBInternalPopupMenuNameKey
// Panel strings:
#define kLIBURLTextKey					kLIBStringPrefix	"kLIBURLTextKey"
#define kLIBFullScreenTextKey					kLIBStringPrefix	"kLIBFullScreenTextKey"
#define kLIBAutoOpenTextKey					kLIBStringPrefix	"kLIBAutoOpenTextKey"

// Menu item positions:

#define	kLIBSeparator1MenuItemPosition		10.0
#define kLIBAboutThisMenuItemPosition		11.0


// Initial data format version numbers
#define kLIBFirstMajorFormatNumber  RezLong(1)
#define kLIBFirstMinorFormatNumber  RezLong(0)

// Data format version numbers for the PluginVersion resource 
#define kLIBCurrentMajorFormatNumber kLIBFirstMajorFormatNumber
#define kLIBCurrentMinorFormatNumber kLIBFirstMinorFormatNumber

#endif // __LIBID_h__

//  Code generated by DollyXs code generator
