    }
    return (res);
}

static content_type *analyze_ct(request_rec *r, const char *s)
{
    const char *cp, *mp, *tmp;
    char *attribute, *value;
    int quoted = 0;
    server_rec * ss = r->server;
    apr_pool_t  * p = r->pool;

    content_type *ctp;
    param *pp, *npp;

    /* initialize ctp */
    ctp = (content_type *) apr_palloc(p, sizeof(content_type));
    ctp->type = NULL;
    ctp->subtype = NULL;
    ctp->param = NULL;

    mp = s;

    /* getting a type */
    if (!(cp = ap_strchr_c(mp, '/'))) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
		     "mod_mime: analyze_ct: cannot get media type from '%s'",
		     (const char *) mp);
	return (NULL);
    }
    ctp->type = zap_sp_and_dup(p, mp, cp, NULL);
    if (ctp->type == NULL || *(ctp->type) == '\0') {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
		     "Cannot get media subtype.");
	return (NULL);
    }
    for (tmp = ctp->type; *tmp; tmp++) {
        if ((*tmp == ';') || (*tmp == ' ') || (*tmp == '\t')) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                         "Cannot get media subtype.");
            return (NULL);
        }
    }

    /* getting a subtype */
    cp++;
    mp = cp;

    for (; *cp != ';' && *cp != '\0'; cp++)
        continue;
    ctp->subtype = zap_sp_and_dup(p, mp, cp, NULL);
    if ((ctp->subtype == NULL) || (*(ctp->subtype) == '\0')) {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
		     "Cannot get media subtype.");
	return (NULL);
    }
    for (tmp = ctp->subtype; *tmp; tmp++) {
        if ((*tmp == ' ') || (*tmp == '\t')) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                         "Cannot get media subtype.");
            return (NULL);
        }
    }
    if (*cp == '\0') {
        return (ctp);
    }

    /* getting parameters */
    cp++;
    cp = zap_sp(cp);
    if (cp == NULL || *cp == '\0') {
	ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
		     "Cannot get media parameter.");
	return (NULL);
    }
