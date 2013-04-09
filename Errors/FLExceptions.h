//
//  FLExceptions.h
//  FishLampFrameworks
//
//  Created by Mike Fullerton on 8/30/12.
//  Copyright (c) 2012 Mike Fullerton. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FLRequired.h"
#import "FLErrorException.h"
#import "FLMutableError.h"
#import "FLStackTrace.h"
#import "FLErrorDomainInfo.h"
#import "FLFrameworkErrorDomain.h"

@interface NSError (FLExceptionCreation)
- (NSException*) createException:(NSDictionary*) userInfo;

- (NSException*) createExceptionWithStackTrace:(FLStackTrace_t) stackTrace 
                                      userInfo:(NSDictionary*) userInfo;
@end

typedef NSException* FLWillThrowExceptionHandler(NSException *exception);

extern void FLSetWillThrowExceptionHandler(FLWillThrowExceptionHandler* handler);

extern FLWillThrowExceptionHandler* FLGetWillThrowExceptionHandler();

#ifndef __INCLUDE_STACK_TRACE__
#define __INCLUDE_STACK_TRACE__ YES
#endif

#define FLThrowException(__EX__) @throw FLGetWillThrowExceptionHandler()(__EX__)

#define FLThrowErrorWithLoc(__ERROR__, __LOC__) \
            FLThrowException([__ERROR__ createExceptionWithStackTrace:FLStackTraceMake(__LOC__, __INCLUDE_STACK_TRACE__) userInfo:nil])

#define FLThrowError(__ERROR__) FLThrowErrorWithLoc(__ERROR__, __FILE_LOCATION__)

#define FLThrowIfError(__OBJECT__) do { NSError* __error = [((id)__OBJECT__) error]; \
                                        if(__error) { \
                                            FLThrowErrorWithLoc(__error, __FILE_LOCATION__); \
                                        } \
                                    } while(0)

#define FLThrowErrorCodeWithComment(__DOMAIN_OBJECT_OR_STRING__, __CODE__, __FORMAT__, ...) \
            FLThrowError([NSError errorWithDomain:__DOMAIN_OBJECT_OR_STRING__ \
                            code:(__CODE__) \
                            localizedDescription: nil \
                            userInfo:nil \
                            comment:FLStringWithFormatOrNil(__FORMAT__, ##__VA_ARGS__)])

#define FLThrowErrorCode(__DOMAIN_OBJECT_OR_STRING__, __CODE__) \
            FLThrowError([NSError errorWithDomain:__DOMAIN_OBJECT_OR_STRING__ \
                            code:(__CODE__) \
                            localizedDescription:nil \
                            userInfo:nil \
                            comment:nil])