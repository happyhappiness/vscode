    return (retval == C_OK) ? REDISMODULE_OK : REDISMODULE_ERR;
}

/* Return the (possibly modified in encoding) input 'str' object if
 * the string is unshared, otherwise NULL is returned. */
RedisModuleString *moduleAssertUnsharedString(RedisModuleString *str) {
    if (str->refcount != 1) {
        serverLog(LL_WARNING,
            "Module attempted to use an in-place string modify operation "
            "with a string referenced multiple times. Please check the code "
            "for API usage correctness.");
        return NULL;
    }
    if (str->encoding == OBJ_ENCODING_EMBSTR) {
        /* Note: here we "leak" the additional allocation that was
         * used in order to store the embedded string in the object. */
        str->ptr = sdsnewlen(str->ptr,sdslen(str->ptr));
        str->encoding = OBJ_ENCODING_RAW;
    } else if (str->encoding == OBJ_ENCODING_INT) {
        /* Convert the string from integer to raw encoding. */
        str->ptr = sdsfromlonglong((long)str->ptr);
        str->encoding = OBJ_ENCODING_RAW;
    }
    return str;
}

/* Append the specified buffere to the string 'str'. The string must be a
 * string created by the user that is referenced only a single time, otherwise
 * REDISMODULE_ERR is returend and the operation is not performed. */
int RM_StringAppendBuffer(RedisModuleCtx *ctx, RedisModuleString *str, const char *buf, size_t len) {
    UNUSED(ctx);
    str = moduleAssertUnsharedString(str);
    if (str == NULL) return REDISMODULE_ERR;
    str->ptr = sdscatlen(str->ptr,buf,len);
    return REDISMODULE_OK;
}

/* --------------------------------------------------------------------------
 * Reply APIs
 *
