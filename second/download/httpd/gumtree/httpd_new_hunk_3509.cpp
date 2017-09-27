        }
    }
#endif /* APR_HAS_SHARED_MEMORY */
    return APR_SUCCESS;
}

/* If detach is non-zero, this is a separate child process,
 * if zero, it is a forked child.
 */
apr_status_t ap_reopen_scoreboard(apr_pool_t *p, apr_shm_t **shm, int detached)
{
#if APR_HAS_SHARED_MEMORY
    if (!detached) {
        return APR_SUCCESS;
    }
    if (apr_shm_size_get(ap_scoreboard_shm) < scoreboard_size) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(00005)
                     "Fatal error: shared scoreboard too small for child!");
        apr_shm_detach(ap_scoreboard_shm);
        ap_scoreboard_shm = NULL;
        return APR_EINVAL;
    }
    /* everything will be cleared shortly */
