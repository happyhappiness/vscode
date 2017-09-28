            continue;
        }
        /* Add the new object in the hash table */
        dbAdd(db,key,val);

        /* Set the expire time if needed */
        if (expiretime != -1) setExpire(db,key,expiretime);

        decrRefCount(key);
    }
    /* Verify the checksum if RDB version is >= 5 */
    if (rdbver >= 5 && server.rdb_checksum) {
        uint64_t cksum, expected = rdb.cksum;

        if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
        memrev64ifbe(&cksum);
        if (cksum == 0) {
            serverLog(LL_WARNING,"RDB file was saved with checksum disabled: no check performed.");
        } else if (cksum != expected) {
            serverLog(LL_WARNING,"Wrong RDB checksum. Aborting now.");
            rdbExitReportCorruptRDB("RDB CRC error");
        }
    }

    fclose(fp);
    stopLoading();
    return C_OK;

eoferr: /* unexpected end of file is handled here with a fatal exit */
    serverLog(LL_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
    rdbExitReportCorruptRDB("Unexpected EOF reading RDB file");
    return C_ERR; /* Just to avoid warning */
}

/* A background saving child (BGSAVE) terminated its work. Handle this.
 * This function covers the case of actual BGSAVEs. */
void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
    if (!bysignal && exitcode == 0) {
        serverLog(LL_NOTICE,
            "Background saving terminated with success");
