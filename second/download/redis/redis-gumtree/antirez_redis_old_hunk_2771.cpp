        }

        if (config.pubsub_mode) {
            if (!config.raw_output)
                printf("Reading messages... (press Ctrl-C to quit)\n");
            while (1) {
                if (cliReadReply(output_raw) != REDIS_OK) exit(1);
