    }
}

/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
static int rdbSave(char *filename) {
    dictIterator *di = NULL;
