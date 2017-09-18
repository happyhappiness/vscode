        return NULL;
    }

    /* take the lock */

    if (rewrite_mapr_lock_acquire) {
        apr_global_mutex_lock(rewrite_mapr_lock_acquire);
    }

    /* write out the request key */
#ifdef NO_WRITEV
    nbytes = strlen(key);
    apr_file_write(fpin, key, &nbytes);
