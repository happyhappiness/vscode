    }
    return (res);
}

static content_type *analyze_ct(request_rec *r, const char *s)
{
    const char *cp, *mp;
    char *attribute, *value;
    int quoted = 0;
    server_rec * ss = r->server;
    apr_pool_t * p = r->pool;

    content_type *ctp;
    param *pp, *npp;

    /* initialize ctp */
    ctp = (content_type *)apr_palloc(p, sizeof(content_type));
    ctp->type = NULL;
    ctp->subtype = NULL;
    ctp->param = NULL;

    mp = s;

    /* getting a type */
    cp = mp;
    while (apr_isspace(*cp)) {
        cp++;
    }
    if (!*cp) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
		     "mod_mime: analyze_ct: cannot get media type from '%s'",
		     (const char *) mp);
	return (NULL);
    }
    ctp->type = cp;
    do {
        cp++;
    } while (*cp && (*cp != '/') && !apr_isspace(*cp) && (*cp != ';'));
    if (!*cp || (*cp == ';')) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                     "Cannot get media type from '%s'",
                     (const char *) mp);
	return (NULL);
    }
    while (apr_isspace(*cp)) {
        cp++;
    }
    if (*cp != '/') {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                     "mod_mime: analyze_ct: cannot get media type from '%s'",
                     (const char *) mp);
        return (NULL);
    }
    ctp->type_len = cp - ctp->type;

    cp++; /* skip the '/' */

    /* getting a subtype */
    while (apr_isspace(*cp)) {
        cp++;
    }
    if (!*cp) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
		     "Cannot get media subtype.");
	return (NULL);
    }
    ctp->subtype = cp;
    do {
        cp++;
    } while (*cp && !apr_isspace(*cp) && (*cp != ';'));
    ctp->subtype_len = cp - ctp->subtype;
    while (apr_isspace(*cp)) {
        cp++;
    }

    if (*cp == '\0') {
        return (ctp);
    }

    /* getting parameters */
    cp++; /* skip the ';' */
    cp = zap_sp(cp);
    if (cp == NULL || *cp == '\0') {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
		     "Cannot get media parameter.");
	return (NULL);
    }
