//
//  NSObject+Blocks.m
//  FishLamp
//
//  Created by Mike Fullerton on 11/5/11.
//  Copyright (c) 2013 GreenTongue Software LLC, Mike Fullerton. 
//  The FishLamp Framework is released under the MIT License: http://fishlamp.com/license 
//

#import "NSObject+Blocks.h"
#import "FLErrorException.h"
#import "FLCancelError.h"

@implementation NSObject (FLBlocks)

+ (void) _performBlock:(void (^)()) block {
    @try {
        if(block) {
            block();
        }
    }
    @catch(NSException* ex) {
        if(!ex.error.isCancelError) {
            @throw;
        }
    
    }
}

- (void) performBlockWithDelay:(NSTimeInterval) delay
                         block:(void (^)()) block {   
    [NSObject performSelector:@selector(_performBlock:) withObject:FLCopyWithAutorelease(block) afterDelay:delay];
}

- (void) performBlockOnMainThread:(void (^)()) block  {
    [NSObject performSelectorOnMainThread:@selector(_performBlock:) withObject:FLCopyWithAutorelease(block) waitUntilDone:NO];
}

+ (void) performBlockOnMainThread:(void (^)()) block  {
    [NSObject performSelectorOnMainThread:@selector(_performBlock:) withObject:FLCopyWithAutorelease(block) waitUntilDone:NO];
}

- (void) performBlockOnMainThreadAndWaitUntilDone:(void (^)()) block {
    [NSObject performSelectorOnMainThread:@selector(_performBlock:) withObject:FLCopyWithAutorelease(block) waitUntilDone:YES];
}

- (void) performBlockOnThread:(NSThread*) thread block:(void (^)()) block {
    [NSObject performSelector:@selector(_performBlock:) onThread:thread withObject:FLCopyWithAutorelease(block) waitUntilDone:NO];
}

+ (void) performBlockOnThread:(NSThread*) thread block:(void (^)()) block {
    [NSObject performSelector:@selector(_performBlock:) onThread:thread withObject:FLCopyWithAutorelease(block) waitUntilDone:NO];
}

@end

