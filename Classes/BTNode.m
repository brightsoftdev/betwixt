//
// Betwixt - Copyright 2012 Three Rings Design

#import "BTNode.h"
#import "BTNode+Package.h"
#import "BTNode+Protected.h"
#import "BTMode.h"

@implementation BTNode

- (void)detach {
    [_parent removeNode:self];
}

- (BTMode*)mode {
    return _parent.mode;
}

- (RAUnitSignal*)attached {
    if (_attached == nil) _attached = [[RAUnitSignal alloc] init];
    return _attached;
}

- (RAUnitSignal*)detached {
    if (_detached == nil) _detached = [[RAUnitSignal alloc] init];
    return _detached;
}

- (RAConnectionGroup*)conns {
    if (_conns == nil) _conns = [[RAConnectionGroup alloc] init];
    return _conns;
}

- (void)removeInternal {
    _parent = nil;
    [_detached emit];
    [self cleanup];
}

- (void)cleanup {
    [_attached disconnectAll];
    [_detached disconnectAll];
    [_conns disconnectAll];
    _isDetached = YES;
}

- (BOOL)isDetached {
    return _isDetached;
}

@synthesize parent=_parent;

@end
