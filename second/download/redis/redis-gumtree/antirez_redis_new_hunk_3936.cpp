        }

        retval = cliReadReply(fd);
        if (!config.raw_output && config.tty) printf("\n");
        if (retval) return retval;
    }
    return 0;
}
