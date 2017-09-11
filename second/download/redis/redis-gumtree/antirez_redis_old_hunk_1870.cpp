    REDIS_NOTUSED(clientData);

    if (config.liveclients == 0) {
        fprintf(stderr,"All clients disconnected... aborting.");
        exit(1);
    }

