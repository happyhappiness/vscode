static int check_speling(request_rec *r)
{
    spconfig *cfg;
    char *good, *bad, *postgood, *url;
    apr_finfo_t dirent;
    int filoc, dotloc, urlen, pglen;
    apr_array_header_t *candidates = NULL;
    apr_dir_t          *dir;

    cfg = ap_get_module_config(r->per_dir_config, &speling_module);
    if (!cfg->enabled) {
        return DECLINED;
    }

    /* We only want to worry about GETs */
    if (r->method_number != M_GET) {
        return DECLINED;
    }

    /* We've already got a file of some kind or another */
    if (r->finfo.filetype != APR_NOFILE) {
        return DECLINED;
    }

    /* Not a file request */
    if (r->proxyreq || !r->filename) {
        return DECLINED;
    }

    /* This is a sub request - don't mess with it */
    if (r->main) {
        return DECLINED;
    }

    /*
     * The request should end up looking like this:
     * r->uri: /correct-url/mispelling/more
     * r->filename: /correct-file/mispelling r->path_info: /more
     *
     * So we do this in steps. First break r->filename into two pieces
     */

    filoc = ap_rind(r->filename, '/');
    /*
     * Don't do anything if the request doesn't contain a slash, or
     * requests "/"
     */
    if (filoc == -1 || strcmp(r->uri, "/") == 0) {
        return DECLINED;
    }

    /* good = /correct-file */
    good = apr_pstrndup(r->pool, r->filename, filoc);
    /* bad = mispelling */
    bad = apr_pstrdup(r->pool, r->filename + filoc + 1);
    /* postgood = mispelling/more */
    postgood = apr_pstrcat(r->pool, bad, r->path_info, NULL);

    urlen = strlen(r->uri);
    pglen = strlen(postgood);

    /* Check to see if the URL pieces add up */
    if (strcmp(postgood, r->uri + (urlen - pglen))) {
        return DECLINED;
    }

    /* url = /correct-url */
    url = apr_pstrndup(r->pool, r->uri, (urlen - pglen));

    /* Now open the directory and do ourselves a check... */
    if (apr_dir_open(&dir, good, r->pool) != APR_SUCCESS) {
        /* Oops, not a directory... */
        return DECLINED;
    }

    candidates = apr_array_make(r->pool, 2, sizeof(misspelled_file));

    dotloc = ap_ind(bad, '.');
    if (dotloc == -1) {
        dotloc = strlen(bad);
    }

    while (apr_dir_read(&dirent, APR_FINFO_DIRENT, dir) == APR_SUCCESS) {
        sp_reason q;

        /*
         * If we end up with a "fixed" URL which is identical to the
         * requested one, we must have found a broken symlink or some such.
         * Do _not_ try to redirect this, it causes a loop!
         */
        if (strcmp(bad, dirent.name) == 0) {
            apr_dir_close(dir);
            return OK;
        }

        /*
         * miscapitalization errors are checked first (like, e.g., lower case
         * file, upper case request)
         */
        else if (strcasecmp(bad, dirent.name) == 0) {
            misspelled_file *sp_new;

            sp_new = (misspelled_file *) apr_array_push(candidates);
            sp_new->name = apr_pstrdup(r->pool, dirent.name);
            sp_new->quality = SP_MISCAPITALIZED;
        }

        /*
         * simple typing errors are checked next (like, e.g.,
         * missing/extra/transposed char)
         */
        else if ((cfg->case_only == 0)
                 && ((q = spdist(bad, dirent.name)) != SP_VERYDIFFERENT)) {
            misspelled_file *sp_new;

            sp_new = (misspelled_file *) apr_array_push(candidates);
            sp_new->name = apr_pstrdup(r->pool, dirent.name);
            sp_new->quality = q;
        }

        /*
         * The spdist() should have found the majority of the misspelled
         * requests.  It is of questionable use to continue looking for
         * files with the same base name, but potentially of totally wrong
         * type (index.html <-> index.db).
         * I would propose to not set the WANT_BASENAME_MATCH define.
         *      08-Aug-1997 <Martin.Kraemer@Mch.SNI.De>
         *
         * However, Alexei replied giving some reasons to add it anyway:
         * > Oh, by the way, I remembered why having the
         * > extension-stripping-and-matching stuff is a good idea:
         * >
         * > If you're using MultiViews, and have a file named foobar.html,
         * > which you refer to as "foobar", and someone tried to access
         * > "Foobar", mod_speling won't find it, because it won't find
         * > anything matching that spelling. With the extension-munging,
         * > it would locate "foobar.html". Not perfect, but I ran into
         * > that problem when I first wrote the module.
         */
        else {
#ifdef WANT_BASENAME_MATCH
            /*
             * Okay... we didn't find anything. Now we take out the hard-core
             * power tools. There are several cases here. Someone might have
             * entered a wrong extension (.htm instead of .html or vice
             * versa) or the document could be negotiated. At any rate, now
             * we just compare stuff before the first dot. If it matches, we
             * figure we got us a match. This can result in wrong things if
             * there are files of different content types but the same prefix
             * (e.g. foo.gif and foo.html) This code will pick the first one
             * it finds. Better than a Not Found, though.
             */
            int entloc = ap_ind(dirent.name, '.');
            if (entloc == -1) {
                entloc = strlen(dirent.name);
            }

            if ((dotloc == entloc)
                && !strncasecmp(bad, dirent.name, dotloc)) {
                misspelled_file *sp_new;

                sp_new = (misspelled_file *) apr_array_push(candidates);
                sp_new->name = apr_pstrdup(r->pool, dirent.name);
                sp_new->quality = SP_VERYDIFFERENT;
            }
#endif
        }
    }
    apr_dir_close(dir);

    if (candidates->nelts != 0) {
        /* Wow... we found us a mispelling. Construct a fixed url */
        char *nuri;
        const char *ref;
        misspelled_file *variant = (misspelled_file *) candidates->elts;
        int i;

        ref = apr_table_get(r->headers_in, "Referer");

        qsort((void *) candidates->elts, candidates->nelts,
              sizeof(misspelled_file), sort_by_quality);

        /*
         * Conditions for immediate redirection:
         *     a) the first candidate was not found by stripping the suffix
         * AND b) there exists only one candidate OR the best match is not
         *        ambiguous
         * then return a redirection right away.
         */
        if (variant[0].quality != SP_VERYDIFFERENT
            && (candidates->nelts == 1
                || variant[0].quality != variant[1].quality)) {

            nuri = ap_escape_uri(r->pool, apr_pstrcat(r->pool, url,
                                                     variant[0].name,
                                                     r->path_info, NULL));
            if (r->parsed_uri.query)
                nuri = apr_pstrcat(r->pool, nuri, "?", r->parsed_uri.query, NULL);

            apr_table_setn(r->headers_out, "Location",
                          ap_construct_url(r->pool, nuri, r));

            ap_log_rerror(APLOG_MARK, APLOG_INFO, APR_SUCCESS,
                          r,
                          ref ? "Fixed spelling: %s to %s from %s"
                              : "Fixed spelling: %s to %s%s",
                          r->uri, nuri,
                          (ref ? ref : ""));

            return HTTP_MOVED_PERMANENTLY;
        }
        /*
         * Otherwise, a "[300] Multiple Choices" list with the variants is
         * returned.
         */
        else {
            apr_pool_t *p;
            apr_table_t *notes;
            apr_pool_t *sub_pool;
            apr_array_header_t *t;
            apr_array_header_t *v;


            if (r->main == NULL) {
                p = r->pool;
                notes = r->notes;
            }
            else {
                p = r->main->pool;
                notes = r->main->notes;
            }

            if (apr_pool_create(&sub_pool, p) != APR_SUCCESS)
                return DECLINED;

            t = apr_array_make(sub_pool, candidates->nelts * 8 + 8,
                              sizeof(char *));
            v = apr_array_make(sub_pool, candidates->nelts * 5,
                              sizeof(char *));

            /* Generate the response text. */

            *(const char **)apr_array_push(t) =
                          "The document name you requested (<code>";
            *(const char **)apr_array_push(t) = ap_escape_html(sub_pool, r->uri);
            *(const char **)apr_array_push(t) =
                           "</code>) could not be found on this server.\n"
                           "However, we found documents with names similar "
                           "to the one you requested.<p>"
                           "Available documents:\n<ul>\n";

            for (i = 0; i < candidates->nelts; ++i) {
                char *vuri;
                const char *reason;

                reason = sp_reason_str[(int) (variant[i].quality)];
                /* The format isn't very neat... */
                vuri = apr_pstrcat(sub_pool, url, variant[i].name, r->path_info,
                                  (r->parsed_uri.query != NULL) ? "?" : "",
                                  (r->parsed_uri.query != NULL)
                                      ? r->parsed_uri.query : "",
                                  NULL);
                *(const char **)apr_array_push(v) = "\"";
                *(const char **)apr_array_push(v) = ap_escape_uri(sub_pool, vuri);
                *(const char **)apr_array_push(v) = "\";\"";
                *(const char **)apr_array_push(v) = reason;
                *(const char **)apr_array_push(v) = "\"";

                *(const char **)apr_array_push(t) = "<li><a href=\"";
                *(const char **)apr_array_push(t) = ap_escape_uri(sub_pool, vuri);
                *(const char **)apr_array_push(t) = "\">";
                *(const char **)apr_array_push(t) = ap_escape_html(sub_pool, vuri);
                *(const char **)apr_array_push(t) = "</a> (";
                *(const char **)apr_array_push(t) = reason;
                *(const char **)apr_array_push(t) = ")\n";

                /*
                 * when we have printed the "close matches" and there are
                 * more "distant matches" (matched by stripping the suffix),
                 * then we insert an additional separator text to suggest
                 * that the user LOOK CLOSELY whether these are really the
                 * files she wanted.
                 */
                if (i > 0 && i < candidates->nelts - 1
                    && variant[i].quality != SP_VERYDIFFERENT
                    && variant[i + 1].quality == SP_VERYDIFFERENT) {
                    *(const char **)apr_array_push(t) =
                                   "</ul>\nFurthermore, the following related "
                                   "documents were found:\n<ul>\n";
                }
            }
            *(const char **)apr_array_push(t) = "</ul>\n";

            /* If we know there was a referring page, add a note: */
            if (ref != NULL) {
                *(const char **)apr_array_push(t) =
                               "Please consider informing the owner of the "
                               "<a href=\"";
                *(const char **)apr_array_push(t) = ap_escape_uri(sub_pool, ref);
                *(const char **)apr_array_push(t) = "\">referring page</a> "
                               "about the broken link.\n";
            }


            /* Pass our apr_table_t to http_protocol.c (see mod_negotiation): */
            apr_table_setn(notes, "variant-list", apr_array_pstrcat(p, t, 0));

            apr_table_mergen(r->subprocess_env, "VARIANTS",
                            apr_array_pstrcat(p, v, ','));

            apr_pool_destroy(sub_pool);

            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                         ref ? "Spelling fix: %s: %d candidates from %s"
                             : "Spelling fix: %s: %d candidates%s",
                         r->uri, candidates->nelts,
                         (ref ? ref : ""));

            return HTTP_MULTIPLE_CHOICES;
        }
    }

    return OK;
}