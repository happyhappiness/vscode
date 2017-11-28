int
main(int argc, char *argv[])
{
    char line[8192];
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
        fprintf( stderr, "error %d %s\n", rc, sasl_errstring(rc, NULL, NULL ));
        fprintf( stdout, "ERR\n" );
        return 1;
    }

#if SASL_VERSION_MAJOR < 2
    rc = sasl_server_new( APP_NAME_SASL, NULL, NULL, NULL, 0, &conn );
#else
    rc = sasl_server_new( APP_NAME_SASL, NULL, NULL, NULL, NULL, NULL, 0, &conn );
#endif

    if ( rc != SASL_OK ) {
        fprintf( stderr, "error %d %s\n", rc, sasl_errstring(rc, NULL, NULL ));
        fprintf( stdout, "ERR\n" );
        return 1;
    }

    while ( fgets( line, sizeof( line ), stdin )) {
        username = &line[0];
        password = strchr( line, '\n' );
        if ( !password) {
            fprintf( stderr, "authenticator: Unexpected input '%s'\n", line );
            fprintf( stdout, "ERR\n" );
            continue;
        }
        *password = '\0';
        password = strchr ( line, ' ' );
        if ( !password) {
            fprintf( stderr, "authenticator: Unexpected input '%s'\n", line );
            fprintf( stdout, "ERR\n" );
            continue;
        }
        *password++ = '\0';

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
                fprintf( stderr, "errstr %s\n", errstr );
            }
            if ( rc != SASL_BADAUTH ) {
                fprintf( stderr, "error %d %s\n", rc, sasl_errstring(rc, NULL, NULL ));
            }
#endif
            fprintf( stdout, "ERR\n" );
        } else {
            fprintf( stdout, "OK\n" );
        }

    }

    sasl_dispose( &conn );
    sasl_done();

    return 0;
}