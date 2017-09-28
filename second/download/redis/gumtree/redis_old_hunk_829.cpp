         * REPLCONF listening-port. */
        if (err[0] == '-') {
            serverLog(LL_NOTICE,"(Non critical) Master does not understand "
                                "REPLCONF listening-port: %s", err);
        }
        sdsfree(err);
        server.repl_state = REPL_STATE_SEND_CAPA;
    }

    /* Inform the master of our capabilities. While we currently send
     * just one capability, it is possible to chain new capabilities here
     * in the form of REPLCONF capa X capa Y capa Z ...
