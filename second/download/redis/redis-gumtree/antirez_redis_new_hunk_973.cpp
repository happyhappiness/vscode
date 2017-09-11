        return 1;
    }
    level = lua_tonumber(lua,-argc);
    if (level < LL_DEBUG || level > LL_WARNING) {
        luaPushError(lua, "Invalid debug level.");
        return 1;
    }
