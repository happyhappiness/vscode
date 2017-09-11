        return 1;
    }
    level = lua_tonumber(lua,-argc);
    if (level < REDIS_DEBUG || level > REDIS_WARNING) {
        luaPushError(lua, "Invalid debug level.");
        return 1;
    }
