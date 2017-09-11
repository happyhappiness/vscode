            addReplyError(c,"Fork() failed: can't run EVAL in debugging mode.");
            return 0;
        } else if (cp == 0) {
            /* Child */
            serverLog(LL_WARNING,"Redis forked for debugging eval");
            closeListeningSockets(0);
        } else {
            /* Parent */
            freeClientAsync(c); /* Close the client in the parent side. */
            return 0;
        }
