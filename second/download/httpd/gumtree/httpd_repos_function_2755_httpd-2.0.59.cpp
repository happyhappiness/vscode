static int ldap_url_parse_ext(const char *url_in, 
                              apr_ldap_url_desc_t **ludpp)
{
/*
 *  Pick apart the pieces of an LDAP URL.
 */
    apr_ldap_url_desc_t *ludp;
    char        *p, *q, *r;
    int         i, enclosed;
    const char  *scheme = NULL;
    const char  *url_tmp;
    char        *url;

    if( url_in == NULL || ludpp == NULL ) {
        return LDAP_URL_ERR_PARAM;
    }

    *ludpp = NULL;  /* pessimistic */

    url_tmp = skip_url_prefix( url_in, &enclosed, &scheme );

    if ( url_tmp == NULL ) {
        return LDAP_URL_ERR_BADSCHEME;
    }

    /* make working copy of the remainder of the URL */
    url = LDAP_STRDUP( url_tmp );
    if ( url == NULL ) {
        return LDAP_URL_ERR_MEM;
    }

    if ( enclosed ) {
        p = &url[strlen(url)-1];

        if( *p != '>' ) {
            LDAP_FREE( url );
            return LDAP_URL_ERR_BADENCLOSURE;
        }

        *p = '\0';
    }

    /* allocate return struct */
    ludp = (apr_ldap_url_desc_t *)LDAP_CALLOC( 1, sizeof( apr_ldap_url_desc_t ));

    if ( ludp == NULL ) {
        LDAP_FREE( url );
        return LDAP_URL_ERR_MEM;
    }

    ludp->lud_next = NULL;
    ludp->lud_host = NULL;
    ludp->lud_port = LDAP_PORT;
    ludp->lud_dn = NULL;
    ludp->lud_attrs = NULL;
    ludp->lud_filter = NULL;
    ludp->lud_scope = -1;
    ludp->lud_filter = NULL;
    ludp->lud_exts = NULL;

    ludp->lud_scheme = LDAP_STRDUP( scheme );

    if ( ludp->lud_scheme == NULL ) {
        LDAP_FREE( url );
        apr_ldap_free_urldesc( ludp );
        return LDAP_URL_ERR_MEM;
    }

    if( strcasecmp( ludp->lud_scheme, "ldaps" ) == 0 ) {
        ludp->lud_port = LDAPS_PORT;
    }

    /* scan forward for '/' that marks end of hostport and begin. of dn */
    p = strchr( url, '/' );

    if( p != NULL ) {
        /* terminate hostport; point to start of dn */
        *p++ = '\0';
    }

    /* IPv6 syntax with [ip address]:port */
    if ( *url == '[' ) {
        r = strchr( url, ']' );
        if ( r == NULL ) {
            LDAP_FREE( url );
            apr_ldap_free_urldesc( ludp );
            return LDAP_URL_ERR_BADURL;
        }
        *r++ = '\0';
        q = strchr( r, ':' );
    } else {
        q = strchr( url, ':' );
    }

    if ( q != NULL ) {
        *q++ = '\0';
        ldap_pvt_hex_unescape( q );

        if( *q == '\0' ) {
            LDAP_FREE( url );
            apr_ldap_free_urldesc( ludp );
            return LDAP_URL_ERR_BADURL;
        }

        ludp->lud_port = atoi( q );
    }

    ldap_pvt_hex_unescape( url );

    /* If [ip address]:port syntax, url is [ip and we skip the [ */
    ludp->lud_host = LDAP_STRDUP( url + ( *url == '[' ) );

    if( ludp->lud_host == NULL ) {
        LDAP_FREE( url );
        apr_ldap_free_urldesc( ludp );
        return LDAP_URL_ERR_MEM;
    }

    /*
     * Kludge.  ldap://111.222.333.444:389??cn=abc,o=company
     *
     * On early Novell releases, search references/referrals were returned
     * in this format, i.e., the dn was kind of in the scope position,
     * but the required slash is missing. The whole thing is illegal syntax,
     * but we need to account for it. Fortunately it can't be confused with
     * anything real.
     */
    if( (p == NULL) && (q != NULL) && ((q = strchr( q, '?')) != NULL)) {
        q++;
        /* ? immediately followed by question */
        if( *q == '?') {
            q++;
            if( *q != '\0' ) {
                /* parse dn part */
                ldap_pvt_hex_unescape( q );
                ludp->lud_dn = LDAP_STRDUP( q );
            } else {
                ludp->lud_dn = LDAP_STRDUP( "" );
            }

            if( ludp->lud_dn == NULL ) {
                LDAP_FREE( url );
                apr_ldap_free_urldesc( ludp );
                return LDAP_URL_ERR_MEM;
            }
        }
    }

    if( p == NULL ) {
        LDAP_FREE( url );
        *ludpp = ludp;
        return LDAP_URL_SUCCESS;
    }

    /* scan forward for '?' that may marks end of dn */
    q = strchr( p, '?' );

    if( q != NULL ) {
        /* terminate dn part */
        *q++ = '\0';
    }

    if( *p != '\0' ) {
        /* parse dn part */
        ldap_pvt_hex_unescape( p );
        ludp->lud_dn = LDAP_STRDUP( p );
    } else {
        ludp->lud_dn = LDAP_STRDUP( "" );
    }

    if( ludp->lud_dn == NULL ) {
        LDAP_FREE( url );
        apr_ldap_free_urldesc( ludp );
        return LDAP_URL_ERR_MEM;
    }

    if( q == NULL ) {
        /* no more */
        LDAP_FREE( url );
        *ludpp = ludp;
        return LDAP_URL_SUCCESS;
    }

    /* scan forward for '?' that may marks end of attributes */
    p = q;
    q = strchr( p, '?' );

    if( q != NULL ) {
        /* terminate attributes part */
        *q++ = '\0';
    }

    if( *p != '\0' ) {
        /* parse attributes */
        ldap_pvt_hex_unescape( p );
        ludp->lud_attrs = ldap_str2charray( p, "," );

        if( ludp->lud_attrs == NULL ) {
            LDAP_FREE( url );
            apr_ldap_free_urldesc( ludp );
            return LDAP_URL_ERR_BADATTRS;
        }
    }

    if ( q == NULL ) {
        /* no more */
        LDAP_FREE( url );
        *ludpp = ludp;
        return LDAP_URL_SUCCESS;
    }

    /* scan forward for '?' that may marks end of scope */
    p = q;
    q = strchr( p, '?' );

    if( q != NULL ) {
        /* terminate the scope part */
        *q++ = '\0';
    }

    if( *p != '\0' ) {
        /* parse the scope */
        ldap_pvt_hex_unescape( p );
        ludp->lud_scope = str2scope( p );

        if( ludp->lud_scope == -1 ) {
            LDAP_FREE( url );
            apr_ldap_free_urldesc( ludp );
            return LDAP_URL_ERR_BADSCOPE;
        }
    }

    if ( q == NULL ) {
        /* no more */
        LDAP_FREE( url );
        *ludpp = ludp;
        return LDAP_URL_SUCCESS;
    }

    /* scan forward for '?' that may marks end of filter */
    p = q;
    q = strchr( p, '?' );

    if( q != NULL ) {
        /* terminate the filter part */
        *q++ = '\0';
    }

    if( *p != '\0' ) {
        /* parse the filter */
        ldap_pvt_hex_unescape( p );

        if( ! *p ) {
            /* missing filter */
            LDAP_FREE( url );
            apr_ldap_free_urldesc( ludp );
            return LDAP_URL_ERR_BADFILTER;
        }

        LDAP_FREE( ludp->lud_filter );
        ludp->lud_filter = LDAP_STRDUP( p );

        if( ludp->lud_filter == NULL ) {
            LDAP_FREE( url );
            apr_ldap_free_urldesc( ludp );
            return LDAP_URL_ERR_MEM;
        }
    }

    if ( q == NULL ) {
        /* no more */
        LDAP_FREE( url );
        *ludpp = ludp;
        return LDAP_URL_SUCCESS;
    }

    /* scan forward for '?' that may marks end of extensions */
    p = q;
    q = strchr( p, '?' );

    if( q != NULL ) {
        /* extra '?' */
        LDAP_FREE( url );
        apr_ldap_free_urldesc( ludp );
        return LDAP_URL_ERR_BADURL;
    }

    /* parse the extensions */
    ludp->lud_exts = ldap_str2charray( p, "," );

    if( ludp->lud_exts == NULL ) {
        LDAP_FREE( url );
        apr_ldap_free_urldesc( ludp );
        return LDAP_URL_ERR_BADEXTS;
    }

    for( i=0; ludp->lud_exts[i] != NULL; i++ ) {
        ldap_pvt_hex_unescape( ludp->lud_exts[i] );

        if( *ludp->lud_exts[i] == '!' ) {
            /* count the number of critical extensions */
            ludp->lud_crit_exts++;
        }
    }

    if( i == 0 ) {
        /* must have 1 or more */
        LDAP_FREE( url );
        apr_ldap_free_urldesc( ludp );
        return LDAP_URL_ERR_BADEXTS;
    }

    /* no more */
    *ludpp = ludp;
    LDAP_FREE( url );
    return LDAP_URL_SUCCESS;
}