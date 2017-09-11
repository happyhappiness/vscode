            printf("Entering slave output mode...  (press Ctrl-C to quit)\n");
            slaveMode();
            config.slave_mode = 0;
            free(argvlen);
            return REDIS_ERR;  /* Error = slaveMode lost connection to master */
        }

        if (cliReadReply(output_raw) != REDIS_OK) {
            free(argvlen);
            return REDIS_ERR;
        } else {
            /* Store database number when SELECT was successfully executed. */
