/**
 * Copyright (c) 2017, Oracle and/or its affiliates.
 * The Universal Permissive License (UPL), Version 1.0
 */


#import "OMLogoutService.h"

@interface OMOIDCLogoutService : OMLogoutService
@property(nonatomic, strong) NSMutableDictionary *authData;
@end
