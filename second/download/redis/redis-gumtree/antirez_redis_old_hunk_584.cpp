        writeToClient(c->fd, c, 0);
        serverLog(LL_WARNING,"Lua debugging session child exiting");
        exitFromChild(0);
    }

    /* Otherwise let's restore client's state. */
