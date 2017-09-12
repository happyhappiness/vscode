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
