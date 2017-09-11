     * To make this function reentrant is futile and makes it slower, but
     * we should at least detect such a misuse, and abort. */
    if (inuse) {
        luaPushError(lua,
            "luaRedisGenericCommand() recursive call detected. Are you doing funny stuff with Lua debug hooks?");
        return 1;
    }
    inuse++;
