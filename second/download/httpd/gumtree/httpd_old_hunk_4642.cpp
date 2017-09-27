    apr_socket_close(sd);
    BIO_free(bio);

    return response;
}

#endif /* HAVE_OCSP */
