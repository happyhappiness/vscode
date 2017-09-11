        luaPushError(lua,
            "Please specify at least one argument for redis.call()");
        inuse--;
        return raise_error ? luaRaiseError(lua) : 1;
    }

    /* Build the arguments vector */
