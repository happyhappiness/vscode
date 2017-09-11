            freeClientAsync(c); /* Close the client in the parent side. */
            return 0;
        }
    } else {
        serverLog(LL_WARNING,
            "Redis synchronous debugging eval session started");
    }

    /* Setup our debugging session. */
