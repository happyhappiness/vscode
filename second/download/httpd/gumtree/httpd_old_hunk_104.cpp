            {
                renegotiate = TRUE;
                /* optimization */

                if ((dc->nOptions & SSL_OPT_OPTRENEGOTIATE) &&
                    (verify_old == SSL_VERIFY_NONE) &&
                    SSL_get_peer_certificate(ssl))
                {
                    renegotiate_quick = TRUE;
                }

                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                             r->server,
                             "Changed client verification type will force "
                             "%srenegotiation",
