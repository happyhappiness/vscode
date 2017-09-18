            if (rc != APR_SUCCESS) {
                /* Bad things happened. Everyone should have cleaned up. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, rc, r,
                              "couldn't create child process: %d: %s", rc, 
                              apr_filename_of_pathname(r->filename));
            }
        }
    } 
    return -1; 
} 

static int cgid_init(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, 
