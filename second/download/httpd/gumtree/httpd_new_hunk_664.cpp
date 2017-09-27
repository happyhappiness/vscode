                }
                else {
                    key = apr_pcalloc(pcgi, sizeof(cgid_req.conn_id));
                    memcpy(key, &cgid_req.conn_id, sizeof(cgid_req.conn_id));
                }
                apr_hash_set(script_hash, key, sizeof(cgid_req.conn_id),
                             (void *)((long)procnew->pid));
            }
        }
    }
    return -1;
}

static int cgid_start(apr_pool_t *p, server_rec *main_server,
                      apr_proc_t *procnew)
{

    daemon_should_exit = 0; /* clear setting from previous generation */
    if ((daemon_pid = fork()) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "mod_cgid: Couldn't spawn cgid daemon process");
        return DECLINED;
    }
