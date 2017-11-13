static int index_directory(request_rec *r,
                           autoindex_config_rec *autoindex_conf)
{
    char *title_name = ap_escape_html(r->pool, r->uri);
    char *title_endp;
    char *name = r->filename;
    char *pstring = NULL;
    apr_finfo_t dirent;
    apr_dir_t *thedir;
    apr_status_t status;
    int num_ent = 0, x;
    struct ent *head, *p;
    struct ent **ar = NULL;
    const char *qstring;
    apr_int32_t autoindex_opts = autoindex_conf->opts;
    char keyid;
    char direction;
    char *colargs;
    char *fullpath;
    apr_size_t dirpathlen;
    char *ctype = "text/html";
    char *charset;

    if ((status = apr_dir_open(&thedir, name, r->pool)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                      "Can't open directory for index: %s", r->filename);
        return HTTP_FORBIDDEN;
    }

    if (autoindex_conf->ctype) {
        ctype = autoindex_conf->ctype;
    }
    if (autoindex_conf->charset) {
        charset = autoindex_conf->charset;
    }
    else {
#if APR_HAS_UNICODE_FS
        charset = "UTF-8";
#else
        charset = "ISO-8859-1";
#endif
    }
    if (*charset) {
        ap_set_content_type(r, apr_pstrcat(r->pool, ctype, ";charset=",
                            charset, NULL));
    }
    else {
        ap_set_content_type(r, ctype);
    }

    if (autoindex_opts & TRACK_MODIFIED) {
        ap_update_mtime(r, r->finfo.mtime);
        ap_set_last_modified(r);
        ap_set_etag(r);
    }
    if (r->header_only) {
        apr_dir_close(thedir);
        return 0;
    }

    /*
     * If there is no specific ordering defined for this directory,
     * default to ascending by filename.
     */
    keyid = autoindex_conf->default_keyid
                ? autoindex_conf->default_keyid : K_NAME;
    direction = autoindex_conf->default_direction
                ? autoindex_conf->default_direction : D_ASCENDING;

    /*
     * Figure out what sort of indexing (if any) we're supposed to use.
     *
     * If no QUERY_STRING was specified or client query strings have been
     * explicitly disabled.
     * If we are ignoring the client, suppress column sorting as well.
     */
    if (autoindex_opts & IGNORE_CLIENT) {
        qstring = NULL;
        autoindex_opts |= SUPPRESS_COLSORT;
        colargs = "";
    }
    else {
        char fval[5], vval[5], *ppre = "", *epattern = "";
        fval[0] = '\0'; vval[0] = '\0';
        qstring = r->args;

        while (qstring && *qstring) {

            /* C= First Sort key Column (N, M, S, D) */
            if (   qstring[0] == 'C' && qstring[1] == '='
                && qstring[2] && strchr(K_VALID, qstring[2])
                && (   qstring[3] == '&' || qstring[3] == ';'
                    || !qstring[3])) {
                keyid = qstring[2];
                qstring += qstring[3] ? 4 : 3;
            }

            /* O= Sort order (A, D) */
            else if (   qstring[0] == 'O' && qstring[1] == '='
                     && (   (qstring[2] == D_ASCENDING)
                         || (qstring[2] == D_DESCENDING))
                     && (   qstring[3] == '&' || qstring[3] == ';'
                         || !qstring[3])) {
                direction = qstring[2];
                qstring += qstring[3] ? 4 : 3;
            }

            /* F= Output Format (0 plain, 1 fancy (pre), 2 table) */
            else if (   qstring[0] == 'F' && qstring[1] == '='
                     && qstring[2] && strchr("012", qstring[2])
                     && (   qstring[3] == '&' || qstring[3] == ';'
                         || !qstring[3])) {
                if (qstring[2] == '0') {
                    autoindex_opts &= ~(FANCY_INDEXING | TABLE_INDEXING);
                }
                else if (qstring[2] == '1') {
                    autoindex_opts = (autoindex_opts | FANCY_INDEXING)
                        & ~TABLE_INDEXING;
                }
                else if (qstring[2] == '2') {
                    autoindex_opts |= FANCY_INDEXING | TABLE_INDEXING;
                }
                strcpy(fval, ";F= ");
                fval[3] = qstring[2];
                qstring += qstring[3] ? 4 : 3;
            }

            /* V= Version sort (0, 1) */
            else if (   qstring[0] == 'V' && qstring[1] == '='
                     && (qstring[2] == '0' || qstring[2] == '1')
                     && (   qstring[3] == '&' || qstring[3] == ';'
                         || !qstring[3])) {
                if (qstring[2] == '0') {
                    autoindex_opts &= ~VERSION_SORT;
                }
                else if (qstring[2] == '1') {
                    autoindex_opts |= VERSION_SORT;
                }
                strcpy(vval, ";V= ");
                vval[3] = qstring[2];
                qstring += qstring[3] ? 4 : 3;
            }

            /* P= wildcard pattern (*.foo) */
            else if (qstring[0] == 'P' && qstring[1] == '=') {
                const char *eos = qstring += 2; /* for efficiency */

                while (*eos && *eos != '&' && *eos != ';') {
                    ++eos;
                }

                if (eos == qstring) {
                    pstring = NULL;
                }
                else {
                    pstring = apr_pstrndup(r->pool, qstring, eos - qstring);
                    if (ap_unescape_url(pstring) != OK) {
                        /* ignore the pattern, if it's bad. */
                        pstring = NULL;
                    }
                    else {
                        ppre = ";P=";
                        /* be correct */
                        epattern = ap_escape_uri(r->pool, pstring);
                    }
                }

                if (*eos && *++eos) {
                    qstring = eos;
                }
                else {
                    qstring = NULL;
                }
            }

            /* Syntax error?  Ignore the remainder! */
            else {
                qstring = NULL;
            }
        }
        colargs = apr_pstrcat(r->pool, fval, vval, ppre, epattern, NULL);
    }

    /* Spew HTML preamble */
    title_endp = title_name + strlen(title_name) - 1;

    while (title_endp > title_name && *title_endp == '/') {
        *title_endp-- = '\0';
    }

    emit_head(r, autoindex_conf->header,
              autoindex_opts & SUPPRESS_PREAMBLE,
              autoindex_opts & EMIT_XHTML, title_name);

    /*
     * Since we don't know how many dir. entries there are, put them into a
     * linked list and then arrayificate them so qsort can use them.
     */
    head = NULL;
    p = make_parent_entry(autoindex_opts, autoindex_conf, r, keyid, direction);
    if (p != NULL) {
        p->next = head;
        head = p;
        num_ent++;
    }
    fullpath = apr_palloc(r->pool, APR_PATH_MAX);
    dirpathlen = strlen(name);
    memcpy(fullpath, name, dirpathlen);

    do {
        status = apr_dir_read(&dirent, APR_FINFO_MIN | APR_FINFO_NAME, thedir);
        if (APR_STATUS_IS_INCOMPLETE(status)) {
            continue; /* ignore un-stat()able files */
        }
        else if (status != APR_SUCCESS) {
            break;
        }

        /* We want to explode symlinks here. */
        if (dirent.filetype == APR_LNK) {
            const char *savename;
            apr_finfo_t fi;
            /* We *must* have FNAME. */
            savename = dirent.name;
            apr_cpystrn(fullpath + dirpathlen, dirent.name,
                        APR_PATH_MAX - dirpathlen);
            status = apr_stat(&fi, fullpath,
                              dirent.valid & ~(APR_FINFO_NAME), r->pool);
            if (status != APR_SUCCESS) {
                /* Something bad happened, skip this file. */
                continue;
            }
            memcpy(&dirent, &fi, sizeof(fi));
            dirent.name = savename;
            dirent.valid |= APR_FINFO_NAME;
        }
        p = make_autoindex_entry(&dirent, autoindex_opts, autoindex_conf, r,
                                 keyid, direction, pstring);
        if (p != NULL) {
            p->next = head;
            head = p;
            num_ent++;
        }
    } while (1);

    if (num_ent > 0) {
        ar = (struct ent **) apr_palloc(r->pool,
                                        num_ent * sizeof(struct ent *));
        p = head;
        x = 0;
        while (p) {
            ar[x++] = p;
            p = p->next;
        }

        qsort((void *) ar, num_ent, sizeof(struct ent *),
              (int (*)(const void *, const void *)) dsortf);
    }
    output_directories(ar, num_ent, autoindex_conf, r, autoindex_opts,
                       keyid, direction, colargs);
    apr_dir_close(thedir);

    emit_tail(r, autoindex_conf->readme,
              autoindex_opts & SUPPRESS_PREAMBLE);

    return 0;
}