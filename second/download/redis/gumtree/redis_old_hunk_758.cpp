            rdbCheckError("RDB CRC error");
        } else {
            rdbCheckInfo("Checksum OK");
        }
    }

    fclose(fp);
    return 0;

eoferr: /* unexpected end of file is handled here with a fatal exit */
    if (rdbstate.error_set) {
        rdbCheckError(rdbstate.error);
    } else {
        rdbCheckError("Unexpected EOF reading RDB file");
    }
    return 1;
}

/* RDB check main: called form redis.c when Redis is executed with the
 * redis-check-rdb alias.
 *
 * The function never returns, but exits with the status code according
 * to success (RDB is sane) or error (RDB is corrupted). */
int redis_check_rdb_main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rdb-file-name>\n", argv[0]);
        exit(1);
    }
    createSharedObjects(); /* Needed for loading. */
    server.loading_process_events_interval_bytes = 0;
    rdbCheckMode = 1;
    rdbCheckInfo("Checking RDB file %s", argv[1]);
    rdbCheckSetupSignals();
    int retval = redis_check_rdb(argv[1]);
    if (retval == 0) {
        rdbCheckInfo("\\o/ RDB looks OK! \\o/");
        rdbShowGenericInfo();
    }
    exit(retval);
}
