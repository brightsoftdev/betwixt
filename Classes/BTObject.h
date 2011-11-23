//
//  Betwixt - Copyright 2011 Three Rings Design

#import <Foundation/Foundation.h>
#import "NSObject+BlockObservation.h"
#import "SPEventDispatcher+BlockListener.h"

#define OBSERVE(OBJ, OBSERVEE, PATH, CODE) \
[(OBJ) observeObject:(OBSERVEE) forKeyPath:(PATH) withBlock:^(id obj, NSDictionary *change) { \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Warc-retain-cycles\"") \
do { CODE; } while(0); \
_Pragma("clang diagnostic pop") \
}];

#define LISTEN(OBJ, DISPATCHER, EVENT_TYPE, CODE) \
[(OBJ) listenToDispatcher:(DISPATCHER) forEvent:(EVENT_TYPE) withBlock:^(SPEvent* event) { \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Warc-retain-cycles\"") \
do { CODE; } while(0); \
_Pragma("clang diagnostic pop") \
}];

@class BTGeneration;

@interface BTObject : NSObject {
@package//Managed by BTGeneration
    BTObject *_next;
    BTGeneration *_gen;
    BTObject *_depHead;
}

- (NSArray*)names;
- (void)addDependentObject:(BTObject*)object;

- (AMBlockToken*)observeObject:(NSObject*)object forKeyPath:(NSString*)path withBlock:(AMBlockTask)block;
- (void)cancelObservationForToken:(AMBlockToken*)token;

- (OOOBlockToken*)listenToDispatcher:(SPEventDispatcher*)dispatcher forEvent:(NSString*)eventType withBlock:(OOOBlockListener)block;
- (void)cancelListeningForToken:(OOOBlockToken*)token;

@property(nonatomic) BOOL added;
@property(nonatomic) BOOL removed;

@end
