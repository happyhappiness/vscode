        }
        luaPushError(lua,
            "Lua redis() command arguments must be strings or integers");
        return 1;
    }

