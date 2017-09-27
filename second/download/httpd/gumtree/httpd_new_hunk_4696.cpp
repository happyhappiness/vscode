
            err = rmm_free(client_rmm, entry);
            num_removed++;

            if (err) {
                /* Nothing we can really do but log... */
                ap_log_error(APLOG_MARK, APLOG_ERR, err, s, APLOGNO(10007)
                             "Failed to free auth_digest client allocation");
            }
        }
    }

    /* update counters and log */
