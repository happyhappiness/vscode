        luaPushError(lua, "redis.log() requires two arguments or more.");
        return 1;
    } else if (!lua_isnumber(lua,-argc)) {
        luaPushError(lua, "First argument must be a number (log level).");
        return 1;
    }
    level = lua_tonumber(lua,-argc);
    if (level < REDIS_DEBUG || level > REDIS_WARNING) {
        luaPushError(lua, "Invalid debug level.");
        return 1;
    }
