    }

    /*
     * Get the SSL connection structure and perform the
     * delayed interlinking from SSL back to request_rec
     */
    if ((ssl = sslconn->ssl)) {
        SSL_set_app_data2(ssl, r);
    }

    return DECLINED;
}

/*
