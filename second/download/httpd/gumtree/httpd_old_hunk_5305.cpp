                 || (mySrvConfig(sslconn->server))->strict_sni_vhost_check
                    == SSL_ENABLED_TRUE)
                 && r->connection->vhost_lookup_data) {
            /*
             * We are using a name based configuration here, but no hostname was
             * provided via SNI. Don't allow that if are requested to do strict
             * checking. Check wether this strict checking was setup either in the
             * server config we used for handshaking or in our current server.
             * This should avoid insecure configuration by accident.
             */
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02033)
                         "No hostname was provided via SNI for a name based"
                         " virtual host");
            return HTTP_FORBIDDEN;
        }
    }
#endif
    SSL_set_app_data2(ssl, r);

