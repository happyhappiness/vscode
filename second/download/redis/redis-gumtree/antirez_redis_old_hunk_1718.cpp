    if (config.liveclients == 0) {
        fprintf(stderr,"All clients disconnected... aborting.\n");
        exit(1);
    }

    if (config.csv) return 250;
    float dt = (float)(mstime()-config.start)/1000.0;
    float rps = (float)config.requests_finished/dt;
    printf("%s: %.2f\r", config.title, rps);
