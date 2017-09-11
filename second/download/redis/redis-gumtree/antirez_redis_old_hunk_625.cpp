        luaPushError(lua,
            "Please specify at least one argument for redis.call()");
        inuse--;
        return 1;
    }

    /* Build the arguments vector */
