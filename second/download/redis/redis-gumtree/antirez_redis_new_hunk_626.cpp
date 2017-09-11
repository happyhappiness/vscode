        luaPushError(lua,
            "Lua redis() command arguments must be strings or integers");
        inuse--;
        return raise_error ? luaRaiseError(lua) : 1;
    }

    /* Setup our fake client for command execution */
