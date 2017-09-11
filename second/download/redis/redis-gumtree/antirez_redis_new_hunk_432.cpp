        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    double scoresum_a = 0;
    double scoresum_b = 0;

    RedisModule_ZsetFirstInRange(key,&zrange);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_FreeString(ctx,ele);
        scoresum_a += score;
        RedisModule_ZsetRangeNext(key);
    }
    RedisModule_ZsetRangeStop(key);

    RedisModule_ZsetLastInRange(key,&zrange);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_FreeString(ctx,ele);
        scoresum_b += score;
        RedisModule_ZsetRangePrev(key);
    }

    RedisModule_ZsetRangeStop(key);

    RedisModule_CloseKey(key);

    RedisModule_ReplyWithArray(ctx,2);
    RedisModule_ReplyWithDouble(ctx,scoresum_a);
    RedisModule_ReplyWithDouble(ctx,scoresum_b);
    return REDISMODULE_OK;
}

