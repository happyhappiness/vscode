        if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
        memrev64ifbe(&cksum);
        if (cksum == 0) {
            serverLog(REDIS_WARNING,"RDB file was saved with checksum disabled: no check performed.");
        } else if (cksum != expected) {
            serverLog(REDIS_WARNING,"Wrong RDB checksum. Aborting now.");
            rdbExitReportCorruptRDB("RDB CRC error");
        }
    }
