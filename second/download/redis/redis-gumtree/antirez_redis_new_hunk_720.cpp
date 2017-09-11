        /* Ignore the error if any, not all the Redis versions support
         * REPLCONF listening-port. */
        if (err[0] == '-') {
            serverLog(LL_NOTICE,"(Non critical) Master does not understand "
                                "REPLCONF listening-port: %s", err);
        }
        sdsfree(err);
    }

    /* Inform the master of our capabilities. While we currently send
     * just one capability, it is possible to chain new capabilities here
     * in the form of REPLCONF capa X capa Y capa Z ...
     * The master will ignore capabilities it does not understand. */
    {
        err = sendSynchronousCommand(fd,"REPLCONF","capa","eof",NULL);

        /* Ignore the error if any, not all the Redis versions support
         * REPLCONF capa. */
        if (err[0] == '-') {
            serverLog(LL_NOTICE,"(Non critical) Master does not understand "
                                  "REPLCONF capa: %s", err);
        }
        sdsfree(err);
    }
