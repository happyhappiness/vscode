static void ssl_state_cb(const SSL *s, int w, int r)
{
    if (w & SSL_CB_ALERT) {
        BIO_printf(bio_err, "SSL/TLS Alert [%s] %s:%s\n",
                   (w & SSL_CB_READ ? "read" : "write"),
                   SSL_alert_type_string_long(r),
                   SSL_alert_desc_string_long(r));
    } else if (w & SSL_CB_LOOP) {
        BIO_printf(bio_err, "SSL/TLS State [%s] %s\n",
                   (SSL_in_connect_init((SSL*)s) ? "connect" : "-"),
                   SSL_state_string_long(s));
    } else if (w & (SSL_CB_HANDSHAKE_START|SSL_CB_HANDSHAKE_DONE)) {
        BIO_printf(bio_err, "SSL/TLS Handshake [%s] %s\n",
                   (w & SSL_CB_HANDSHAKE_START ? "Start" : "Done"),
                   SSL_state_string_long(s));
    }
}