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
    mp = cp;
    attribute = NULL;
    value = NULL;

    while (cp != NULL && *cp != '\0') {
        if (attribute == NULL) {
            if (is_token(*cp) > 0) {
                cp++;
                continue;
            }
            else if (*cp == ' ' || *cp == '\t' || *cp == '\n') {
                cp++;
                continue;
            }
            else if (*cp == '=') {
                attribute = zap_sp_and_dup(p, mp, cp, NULL);
                if (attribute == NULL || *attribute == '\0') {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                 "Cannot get media parameter.");
                    return (NULL);
                }
                cp++;
                cp = zap_sp(cp);
                if (cp == NULL || *cp == '\0') {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                 "Cannot get media parameter.");
                    return (NULL);
                }
                mp = cp;
                continue;
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                             "Cannot get media parameter.");
                return (NULL);
            }
        }
        else {
            if (mp == cp) {
                if (*cp == '"') {
                    quoted = 1;
                    cp++;
                }
                else {
                    quoted = 0;
                }
            }
            if (quoted > 0) {
                while (quoted && *cp != '\0') {
                    if (is_qtext(*cp) > 0) {
                        cp++;
                    }
                    else if (is_quoted_pair(cp) > 0) {
                        cp += 2;
                    }
                    else if (*cp == '"') {
                        cp++;
                        while (*cp == ' ' || *cp == '\t' || *cp == '\n') {
                            cp++;
                        }
                        if (*cp != ';' && *cp != '\0') {
                            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                         "Cannot get media parameter.");
                            return(NULL);
                        }
                        quoted = 0;
                    }
                    else {
                        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                     "Cannot get media parameter.");
                        return (NULL);
                    }
                }
            }
            else {
                while (1) {
                    if (is_token(*cp) > 0) {
                        cp++;
                    }
                    else if (*cp == '\0' || *cp == ';') {
                        break;
                    }
                    else {
                        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                                     "Cannot get media parameter.");
                        return (NULL);
                    }
                }
            }
            value = zap_sp_and_dup(p, mp, cp, NULL);
            if (value == NULL || *value == '\0') {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ss,
                             "Cannot get media parameter.");
                return (NULL);
            }

            pp = apr_palloc(p, sizeof(param));
            pp->attr = attribute;
            pp->val = value;
            pp->next = NULL;

            if (ctp->param == NULL) {
                ctp->param = pp;
            }
            else {
                npp = ctp->param;
                while (npp->next) {
                    npp = npp->next;
                }
                npp->next = pp;
            }
            quoted = 0;
            attribute = NULL;
            value = NULL;
            if (*cp == '\0') {
                break;
            }
            cp++;
            mp = cp;
        }
    }
    return (ctp);
}