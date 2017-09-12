            printf("Reading messages... (press Ctrl-c to quit)\n");
            while (1) {
                cliReadReply(fd);
                printf("\n\n");
            }
        }

        retval = cliReadReply(fd);
        if (retval) {
            return retval;
        }
        if (!config.raw_output && config.tty) {
            printf("\n");
        }
    }
    return 0;
}
