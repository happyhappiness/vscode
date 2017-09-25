                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                             "couldn't create child process: %d: %s", rc, 
                             apr_filename_of_pathname(r->filename));
            }
            else {
                apr_hash_set(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id), 
                             (void *)procnew->pid);
            }
        }
    } 
    return -1; 
} 
