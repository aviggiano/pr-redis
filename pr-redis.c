#include "redismodule.h"
#include <limits.h>

int CrashCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx);

    RedisModuleString *skey = RedisModule_CreateString(ctx, "key", sizeof("key")-1);
    RedisModuleString *sfield = RedisModule_CreateString(ctx, "field", sizeof("field")-1);
    RedisModuleCallReply *rep = RedisModule_Call(ctx, "HSET", "ssl", skey, sfield, (long long) 1);

    RedisModule_ReplyWithCallReply(ctx, rep);

    return REDISMODULE_OK;
}

int DoesNotCrashCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx);

    RedisModuleString *skey = RedisModule_CreateString(ctx, "KEY", sizeof("KEY")-1);
    RedisModuleString *svalue = RedisModule_CreateString(ctx, "VALUE", sizeof("VALUE")-1);
    RedisModuleCallReply *rep = RedisModule_Call(ctx, "LPUSH", "ssl", skey, svalue, (long long) 1);

    RedisModule_ReplyWithCallReply(ctx, rep);

    return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx) {
    // Register the module itself
    if (RedisModule_Init(ctx, "PR_REDIS", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }

    // register our command
    if (RedisModule_CreateCommand(ctx, "CRASH", CrashCommand, "write", 1, 1, 1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }
    if (RedisModule_CreateCommand(ctx, "DOES_NOT_CRASH", DoesNotCrashCommand, "write", 1, 1, 1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }

    return REDISMODULE_OK;
}


