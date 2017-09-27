#endif
    }

    return rv;
}

#if APR_HAS_THREADS
static apr_status_t dbd_setup_lock(server_rec *s, dbd_group_t *group)
{
    apr_status_t rv = APR_SUCCESS, rv2;

    /* several threads could be here at the same time, all trying to
