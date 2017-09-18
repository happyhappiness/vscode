            rc = ap_os_create_privileged_process(r, procnew, argv0, argv, 
                                                 (const char * const *)env, 
                                                 procattr, ptrans);

            if (rc != APR_SUCCESS) {
                /* Bad things happened. Everyone should have cleaned up. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                        "couldn't create child process: %d: %s", rc, r->filename);
            }
        }
    } 
    return -1; 
} 

