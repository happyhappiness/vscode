            }
        }

        if (cliReadReply(output_raw) != REDIS_OK) {
            free(argvlen);
            return REDIS_ERR;
