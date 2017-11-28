int
main(int, char *argv[])
{
    char line[HELPER_INPUT_BUFFER];
    char *username, *password;
#if SASL_VERSION_MAJOR < 2
    const char *errstr;
#endif

    int rc;
    sasl_conn_t *conn = NULL;

    /* make standard output line buffered */
    setvbuf(stdout, NULL, _IOLBF, 0);

    rc = sasl_server_init( NULL, APP_NAME_SASL );

    if ( rc != SASL_OK ) {
        fprintf(stderr, "FATAL: %d %s\n", rc, sasl_errstring(rc, NULL, NULL ));
        return 1;
    }

#if SASL_VERSION_MAJOR < 2
    rc = sasl_server_new( APP_NAME_SASL, NULL, NULL, NULL, 0, &conn );
#else
    rc = sasl_server_new( APP_NAME_SASL, NULL, NULL, NULL, NULL, NULL, 0, &conn );
#endif

    if ( rc != SASL_OK ) {
        fprintf(stderr, "FATAL: %d %s\n", rc, sasl_errstring(rc, NULL, NULL ));
        return 1;
    }

    while ( fgets( line, HELPER_INPUT_BUFFER, stdin )) {
        username = &line[0];
        password = strchr( line, '\n' );
        if (!password) {
            debug("ERROR: %s: Unexpected input '%s'\n", argv[0], line);
            SEND_ERR("Unexpected Empty Input");
            continue;
        }
        *password = '\0';
        password = strchr ( line, ' ' );
        if (!password) {
            debug("ERROR: %s: Unexpected input '%s' (no password)\n", argv[0], line );
            SEND_ERR("No Password");
            continue;
        }
        *password = '\0';
        ++password;

        rfc1738_unescape(username);
        rfc1738_unescape(password);

#if SASL_VERSION_MAJOR < 2
        rc = sasl_checkpass(conn, username, strlen(username), password, strlen(password), &errstr);
#else
        rc = sasl_checkpass(conn, username, strlen(username), password, strlen(password));
#endif

        if ( rc != SASL_OK ) {
#if SASL_VERSION_MAJOR < 2
            if ( errstr ) {
                debug("errstr %s\n", errstr);
            }
            if ( rc != SASL_BADAUTH ) {
                debug("ERROR: %d %s\n", rc, sasl_errstring(rc, NULL, NULL));
                SEND_ERR(sasl_errstring(rc, NULL, NULL));
            } else
#endif
                SEND_ERR("");
        } else {
            SEND_OK("");
        }
    }

    sasl_dispose(&conn);
    sasl_done();
    return 0;
}