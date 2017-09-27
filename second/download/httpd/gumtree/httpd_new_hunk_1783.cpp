         * There is one special filter callback, which is set
         * very early depending on the base_server's log level.
         * If this is not the first vhost we're now selecting
         * (and the first vhost doesn't use APLOG_DEBUG), then
         * we need to set that callback here.
         */
        if (APLOGdebug(s)) {
            BIO_set_callback(SSL_get_rbio(ssl), ssl_io_data_cb);
            BIO_set_callback_arg(SSL_get_rbio(ssl), (void *)ssl);
        }

        return 1;
    }

    return 0;
}
#endif
