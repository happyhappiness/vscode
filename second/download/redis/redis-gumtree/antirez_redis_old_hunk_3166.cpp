    return 1;
}

void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
    long long elapsed;
    REDIS_NOTUSED(ar);
