                             "shmcb_remove_session_id, internal error");
                goto end;
            }
            session_id_length = SSL_SESSION_get_session_id_length(pSession);
            session_id = SSL_SESSION_get_session_id(pSession);

            if ((session_id_length == idlen) 
                 && (memcmp(id, session_id, idlen) == 0)) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                            "a match!");
                /* Scrub out this session "quietly" */
                idx->removed = (unsigned char) 1;
                SSL_SESSION_free(pSession);
