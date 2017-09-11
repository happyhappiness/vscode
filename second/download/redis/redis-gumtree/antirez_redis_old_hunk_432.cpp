        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    RedisModule_ZsetFirstInRange(key,&zrange);
    double scoresum = 0;
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_FreeString(ctx,ele);
        scoresum += score;
        RedisModule_ZsetRangeNext(key);
    }
    RedisModule_ZsetRangeStop(key);
    RedisModule_CloseKey(key);
    RedisModule_ReplyWithDouble(ctx,scoresum);
    return REDISMODULE_OK;
}

