

    for ( ; *cp && *cp != ':' ; ++cp) {

        *cp = ap_tolower(*cp);

    }



    if (!*cp) {

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                    "Syntax error in type map --- no ':': %s", r->filename);

        return NULL;

    }



    do {

        ++cp;

    } while (*cp && ap_isspace(*cp));



    if (!*cp) {

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                    "Syntax error in type map --- no header body: %s",

                    r->filename);

        return NULL;

    }



    return cp;

