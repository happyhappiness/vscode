        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    /* XXX modify me. */
    RedisModule_HashSet(key,REDISMODULE_HSET_NONE,argv[2],argv[3],NULL);
    RedisModule_HashSet(key,REDISMODULE_HSET_CFIELDS,"foo",argv[3],NULL);
    RedisModule_ReplyWithLongLong(ctx,0);
    return REDISMODULE_OK;
}

