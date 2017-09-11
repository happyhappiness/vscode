        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    /* Get the old field value. */
    RedisModuleString *oldval;
    RedisModule_HashGet(key,REDISMODULE_HGET_NONE,argv[2],&oldval,NULL);
    if (oldval) {
        RedisModule_HashSet(key,REDISMODULE_HSET_NONE,argv[3],oldval,NULL);
    }
    RedisModule_ReplyWithLongLong(ctx,oldval != NULL);
    return REDISMODULE_OK;
}

