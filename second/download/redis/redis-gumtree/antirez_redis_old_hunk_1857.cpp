            printf("Entering slave output mode...  (press Ctrl-C to quit)\n");
            slaveMode();
            config.slave_mode = 0;
            return REDIS_ERR;  /* Error = slaveMode lost connection to master */
        }

