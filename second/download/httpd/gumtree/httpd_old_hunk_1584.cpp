                 * ap_log_rerror() won't work because the header table used by
                 * ap_log_rerror() hasn't been replicated in the phony r
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                             "couldn't create child process: %d: %s", rc,
                             apr_filepath_name_get(r->filename));
            }
            else {
                /* We don't want to leak storage for the key, so only allocate
                 * a key if the key doesn't exist yet in the hash; there are
                 * only a limited number of possible keys (one for each
                 * possible thread in the server), so we can allocate a copy
                 * of the key the first time a thread has a cgid request.
                 * Note that apr_hash_set() only uses the storage passed in
                 * for the key if it is adding the key to the hash for the
                 * first time; new key storage isn't needed for replacing the
                 * existing value of a key.
                 */
                void *key;

                if (apr_hash_get(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id))) {
                    key = &cgid_req.conn_id;
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
    return -1; /* should be <= 0 to distinguish from startup errors */
}

static int cgid_start(apr_pool_t *p, server_rec *main_server,
                      apr_proc_t *procnew)
