        }
        luaPushError(lua,
            "Lua redis() command arguments must be strings or integers");
        inuse--;
        return 1;
    }

