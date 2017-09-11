    }
    
    /* Connect */
    fd = migrateGetSocket(c,c->argv[1],c->argv[2],timeout);
    if (fd == -1) return; /* error sent to the client by migrateGetSocket() */

    /* Create RESTORE payload and generate the protocol to call the command. */
    rioInitWithBuffer(&cmd,sdsempty());
