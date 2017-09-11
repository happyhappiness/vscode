    return REDISMODULE_OK;
}

/* This Redis command binds the normal Redis command invocation with commands
 * exported by modules. */
void RedisModuleCommandDispatcher(client *c) {
