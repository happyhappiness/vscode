            printf("Entering slave output mode...  (press Ctrl-C to quit)\n");
            slaveMode();
            config.slave_mode = 0;
            zfree(argvlen);
            return REDIS_ERR;  /* Error = slaveMode lost connection to master */
        }

        if (cliReadReply(output_raw) != REDIS_OK) {
            zfree(argvlen);
            return REDIS_ERR;
        } else {
            /* Store database number when SELECT was successfully executed. */
