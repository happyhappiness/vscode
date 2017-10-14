static apr_status_t proxy_send_dir_filter(ap_filter_t *f,
                                          apr_bucket_brigade *in)
{
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    apr_pool_t *p = r->pool;
    apr_bucket_brigade *out = apr_brigade_create(p, c->bucket_alloc);
    apr_status_t rv;

    register int n;
    char *dir, *path, *reldir, *site, *str, *type;

    const char *pwd = apr_table_get(r->notes, "Directory-PWD");
    const char *readme = apr_table_get(r->notes, "Directory-README");

    proxy_dir_ctx_t *ctx = f->ctx;

    if (!ctx) {
        f->ctx = ctx = apr_pcalloc(p, sizeof(*ctx));
        ctx->in = apr_brigade_create(p, c->bucket_alloc);
        ctx->buffer[0] = 0;
        ctx->state = HEADER;
    }

    /* combine the stored and the new */
    APR_BRIGADE_CONCAT(ctx->in, in);

    if (HEADER == ctx->state) {

        /* basedir is either "", or "/%2f" for the "squid %2f hack" */
        const char *basedir = "";  /* By default, path is relative to the $HOME dir */
        char *wildcard = NULL;
        const char *escpath;

        /*
         * In the reverse proxy case we need to construct our site string
         * via ap_construct_url. For non anonymous sites apr_uri_unparse would
         * only supply us with 'username@' which leads to the construction of
         * an invalid base href later on. Losing the username part of the URL
         * is no problem in the reverse proxy case as the browser sents the
         * credentials anyway once entered.
         */
        if (r->proxyreq == PROXYREQ_REVERSE) {
            site = ap_construct_url(p, "", r);
        }
        else {
            /* Save "scheme://site" prefix without password */
            site = apr_uri_unparse(p, &f->r->parsed_uri,
                                   APR_URI_UNP_OMITPASSWORD |
                                   APR_URI_UNP_OMITPATHINFO);
        }

        /* ... and path without query args */
        path = apr_uri_unparse(p, &f->r->parsed_uri, APR_URI_UNP_OMITSITEPART | APR_URI_UNP_OMITQUERY);

        /* If path began with /%2f, change the basedir */
        if (strncasecmp(path, "/%2f", 4) == 0) {
            basedir = "/%2f";
        }

        /* Strip off a type qualifier. It is ignored for dir listings */
        if ((type = strstr(path, ";type=")) != NULL)
            *type++ = '\0';

        (void)decodeenc(path);

        while (path[1] == '/') /* collapse multiple leading slashes to one */
            ++path;

        reldir = strrchr(path, '/');
        if (reldir != NULL && ftp_check_globbingchars(reldir)) {
            wildcard = &reldir[1];
            reldir[0] = '\0'; /* strip off the wildcard suffix */
        }

        /* Copy path, strip (all except the last) trailing slashes */
        /* (the trailing slash is needed for the dir component loop below) */
        path = dir = apr_pstrcat(p, path, "/", NULL);
        for (n = strlen(path); n > 1 && path[n - 1] == '/' && path[n - 2] == '/'; --n)
            path[n - 1] = '\0';

        /* Add a link to the root directory (if %2f hack was used) */
        str = (basedir[0] != '\0') ? "<a href=\"/%2f/\">%2f</a>/" : "";

        /* print "ftp://host/" */
        escpath = ap_escape_html(p, path);
        str = apr_psprintf(p, DOCTYPE_HTML_3_2
                "<html>\n <head>\n  <title>%s%s%s</title>\n"
                "<base href=\"%s%s%s\">\n"
                " </head>\n"
                " <body>\n  <h2>Directory of "
                "<a href=\"/\">%s</a>/%s",
                site, basedir, escpath, site, basedir, escpath, site, str);

        APR_BRIGADE_INSERT_TAIL(out, apr_bucket_pool_create(str, strlen(str),
                                                          p, c->bucket_alloc));

        for (dir = path+1; (dir = strchr(dir, '/')) != NULL; )
        {
            *dir = '\0';
            if ((reldir = strrchr(path+1, '/'))==NULL) {
                reldir = path+1;
            }
            else
                ++reldir;
            /* print "path/" component */
            str = apr_psprintf(p, "<a href=\"%s%s/\">%s</a>/", basedir,
                        ap_escape_uri(p, path),
                        ap_escape_html(p, reldir));
            *dir = '/';
            while (*dir == '/')
              ++dir;
            APR_BRIGADE_INSERT_TAIL(out, apr_bucket_pool_create(str,
                                                           strlen(str), p,
                                                           c->bucket_alloc));
        }
        if (wildcard != NULL) {
            wildcard = ap_escape_html(p, wildcard);
            APR_BRIGADE_INSERT_TAIL(out, apr_bucket_pool_create(wildcard,
                                                           strlen(wildcard), p,
                                                           c->bucket_alloc));
        }

        /* If the caller has determined the current directory, and it differs */
        /* from what the client requested, then show the real name */
        if (pwd == NULL || strncmp(pwd, path, strlen(pwd)) == 0) {
            str = apr_psprintf(p, "</h2>\n\n  <hr />\n\n<pre>");
        }
        else {
            str = apr_psprintf(p, "</h2>\n\n(%s)\n\n  <hr />\n\n<pre>",
                               ap_escape_html(p, pwd));
        }
        APR_BRIGADE_INSERT_TAIL(out, apr_bucket_pool_create(str, strlen(str),
                                                           p, c->bucket_alloc));

        /* print README */
        if (readme) {
            str = apr_psprintf(p, "%s\n</pre>\n\n<hr />\n\n<pre>\n",
                               ap_escape_html(p, readme));

            APR_BRIGADE_INSERT_TAIL(out, apr_bucket_pool_create(str,
                                                           strlen(str), p,
                                                           c->bucket_alloc));
        }

        /* make sure page intro gets sent out */
        APR_BRIGADE_INSERT_TAIL(out, apr_bucket_flush_create(c->bucket_alloc));
        if (APR_SUCCESS != (rv = ap_pass_brigade(f->next, out))) {
            return rv;
        }
        apr_brigade_cleanup(out);

        ctx->state = BODY;
    }

    /* loop through each line of directory */
    while (BODY == ctx->state) {
        char *filename;
        int found = 0;
        int eos = 0;

        ap_regex_t *re = NULL;
        ap_regmatch_t re_result[LS_REG_MATCH];

        /* Compile the output format of "ls -s1" as a fallback for non-unix ftp listings */
        re = ap_pregcomp(p, LS_REG_PATTERN, AP_REG_EXTENDED);
        ap_assert(re != NULL);

        /* get a complete line */
        /* if the buffer overruns - throw data away */
        while (!found && !APR_BRIGADE_EMPTY(ctx->in)) {
            char *pos, *response;
            apr_size_t len, max;
            apr_bucket *e;

            e = APR_BRIGADE_FIRST(ctx->in);
            if (APR_BUCKET_IS_EOS(e)) {
                eos = 1;
                break;
            }
            if (APR_SUCCESS != (rv = apr_bucket_read(e, (const char **)&response, &len, APR_BLOCK_READ))) {
                return rv;
            }
            pos = memchr(response, APR_ASCII_LF, len);
            if (pos != NULL) {
                if ((response + len) != (pos + 1)) {
                    len = pos - response + 1;
                    apr_bucket_split(e, pos - response + 1);
                }
                found = 1;
            }
            max = sizeof(ctx->buffer) - strlen(ctx->buffer) - 1;
            if (len > max) {
                len = max;
            }

            /* len+1 to leave space for the trailing nil char */
            apr_cpystrn(ctx->buffer+strlen(ctx->buffer), response, len+1);

            APR_BUCKET_REMOVE(e);
            apr_bucket_destroy(e);
        }

        /* EOS? jump to footer */
        if (eos) {
            ctx->state = FOOTER;
            break;
        }

        /* not complete? leave and try get some more */
        if (!found) {
            return APR_SUCCESS;
        }

        {
            apr_size_t n = strlen(ctx->buffer);
            if (ctx->buffer[n-1] == CRLF[1])  /* strip trailing '\n' */
                ctx->buffer[--n] = '\0';
            if (ctx->buffer[n-1] == CRLF[0])  /* strip trailing '\r' if present */
                ctx->buffer[--n] = '\0';
        }

        /* a symlink? */
        if (ctx->buffer[0] == 'l' && (filename = strstr(ctx->buffer, " -> ")) != NULL) {
            char *link_ptr = filename;

            do {
                filename--;
            } while (filename[0] != ' ' && filename > ctx->buffer);
            if (filename > ctx->buffer)
                *(filename++) = '\0';
            *(link_ptr++) = '\0';
            str = apr_psprintf(p, "%s <a href=\"%s\">%s %s</a>\n",
                               ap_escape_html(p, ctx->buffer),
                               ap_escape_uri(p, filename),
                               ap_escape_html(p, filename),
                               ap_escape_html(p, link_ptr));
        }

        /* a directory/file? */
        else if (ctx->buffer[0] == 'd' || ctx->buffer[0] == '-' || ctx->buffer[0] == 'l' || apr_isdigit(ctx->buffer[0])) {
            int searchidx = 0;
            char *searchptr = NULL;
            int firstfile = 1;
            if (apr_isdigit(ctx->buffer[0])) {  /* handle DOS dir */
                searchptr = strchr(ctx->buffer, '<');
                if (searchptr != NULL)
                    *searchptr = '[';
                searchptr = strchr(ctx->buffer, '>');
                if (searchptr != NULL)
                    *searchptr = ']';
            }

            filename = strrchr(ctx->buffer, ' ');
            if (filename == NULL) {
                /* Line is broken.  Ignore it. */
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                             "proxy_ftp: could not parse line %s", ctx->buffer);
                /* erase buffer for next time around */
                ctx->buffer[0] = 0;
                continue;  /* while state is BODY */
            }
            *(filename++) = '\0';

            /* handle filenames with spaces in 'em */
            if (!strcmp(filename, ".") || !strcmp(filename, "..") || firstfile) {
                firstfile = 0;
                searchidx = filename - ctx->buffer;
            }
            else if (searchidx != 0 && ctx->buffer[searchidx] != 0) {
                *(--filename) = ' ';
                ctx->buffer[searchidx - 1] = '\0';
                filename = &ctx->buffer[searchidx];
            }

            /* Append a slash to the HREF link for directories */
            if (!strcmp(filename, ".") || !strcmp(filename, "..") || ctx->buffer[0] == 'd') {
                str = apr_psprintf(p, "%s <a href=\"%s/\">%s</a>\n",
                                   ap_escape_html(p, ctx->buffer),
                                   ap_escape_uri(p, filename),
                                   ap_escape_html(p, filename));
            }
            else {
                str = apr_psprintf(p, "%s <a href=\"%s\">%s</a>\n",
                                   ap_escape_html(p, ctx->buffer),
                                   ap_escape_uri(p, filename),
                                   ap_escape_html(p, filename));
            }
        }
        /* Try a fallback for listings in the format of "ls -s1" */
        else if (0 == ap_regexec(re, ctx->buffer, LS_REG_MATCH, re_result, 0)) {

            filename = apr_pstrndup(p, &ctx->buffer[re_result[2].rm_so], re_result[2].rm_eo - re_result[2].rm_so);

            str = apr_pstrcat(p, ap_escape_html(p, apr_pstrndup(p, ctx->buffer, re_result[2].rm_so)),
                              "<a href=\"", ap_escape_uri(p, filename), "\">",
                              ap_escape_html(p, filename), "</a>\n", NULL);
        }
        else {
            strcat(ctx->buffer, "\n"); /* re-append the newline */
            str = ap_escape_html(p, ctx->buffer);
        }

        /* erase buffer for next time around */
        ctx->buffer[0] = 0;

        APR_BRIGADE_INSERT_TAIL(out, apr_bucket_pool_create(str, strlen(str), p,
                                                            c->bucket_alloc));
        APR_BRIGADE_INSERT_TAIL(out, apr_bucket_flush_create(c->bucket_alloc));
        if (APR_SUCCESS != (rv = ap_pass_brigade(f->next, out))) {
            return rv;
        }
        apr_brigade_cleanup(out);

    }

    if (FOOTER == ctx->state) {
        str = apr_psprintf(p, "</pre>\n\n  <hr />\n\n  %s\n\n </body>\n</html>\n", ap_psignature("", r));
        APR_BRIGADE_INSERT_TAIL(out, apr_bucket_pool_create(str, strlen(str), p,
                                                            c->bucket_alloc));
        APR_BRIGADE_INSERT_TAIL(out, apr_bucket_flush_create(c->bucket_alloc));
        APR_BRIGADE_INSERT_TAIL(out, apr_bucket_eos_create(c->bucket_alloc));
        if (APR_SUCCESS != (rv = ap_pass_brigade(f->next, out))) {
            return rv;
        }
        apr_brigade_destroy(out);
    }

    return APR_SUCCESS;
}