//
//  FLStructFlagsProperty.h
//  FishLampFrameworks
//
//  Created by Mike Fullerton on 9/2/12.
//  Copyright (c) 2012 Mike Fullerton. All rights reserved.
//

#import "FLRequired.h"

// WARNING: don't import anything here. This file is imported by FishLamp.  This is imported by everything.
#define FLSynthesizeStructGetterProperty(GET_NAME, __TYPE__, STRUCT) \
	- (__TYPE__) GET_NAME { return (__TYPE__) STRUCT.GET_NAME; } 

#define FLSynthesizeStructProperty(GET_NAME, SET_NAME, __TYPE__, STRUCT) \
	- (__TYPE__) GET_NAME { return (__TYPE__) STRUCT.GET_NAME; } \
	- (void) SET_NAME:(__TYPE__) inValue { STRUCT.GET_NAME = (__TYPE__) inValue; }
