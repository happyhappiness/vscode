            if (err == SSL_ERROR_ZERO_RETURN) {
                /*
                 * The case where the connection was closed before any data
                 * was transferred. That's not a real error and can occur
                 * sporadically with some clients.
                 */
                ssl_log(c->base_server, SSL_LOG_INFO,
                        "SSL handshake stopped: connection was closed");
            }
            else if (err == SSL_ERROR_WANT_READ) {
                /*
                 * This is in addition to what was present earlier. It is 
                 * borrowed from openssl_state_machine.c [mod_tls].
                 * TBD.
