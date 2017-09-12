luaPushError(lua,
            "luaRedisGenericCommand() recursive call detected. Are you doing funny stuff with Lua debug hooks?");