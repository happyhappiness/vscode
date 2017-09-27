    }
    free(asn1);

    apr_hash_set(table, key, klen, NULL);
}

#if APR_HAS_THREADS
/*
 * To ensure thread-safetyness in OpenSSL - work in progress
 */

static apr_thread_mutex_t **lock_cs;
