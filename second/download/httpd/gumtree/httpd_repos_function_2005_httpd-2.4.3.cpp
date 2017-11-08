static apr_status_t do_pattmatch(ap_filter_t *f, apr_bucket *inb,
                                 apr_bucket_brigade *mybb,
                                 apr_pool_t *pool)
{
    int i;
    int force_quick = 0;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
    apr_size_t bytes;
    apr_size_t len;
    const char *buff;
    struct ap_varbuf vb;
    apr_bucket *b;
    apr_bucket *tmp_b;

    subst_dir_conf *cfg =
    (subst_dir_conf *) ap_get_module_config(f->r->per_dir_config,
                                             &substitute_module);
    subst_pattern_t *script;

    APR_BRIGADE_INSERT_TAIL(mybb, inb);
    ap_varbuf_init(pool, &vb, 0);

    script = (subst_pattern_t *) cfg->patterns->elts;
    /*
     * Simple optimization. If we only have one pattern, then
     * we can safely avoid the overhead of flattening
     */
    if (cfg->patterns->nelts == 1) {
       force_quick = 1;
    }
    for (i = 0; i < cfg->patterns->nelts; i++) {
        for (b = APR_BRIGADE_FIRST(mybb);
             b != APR_BRIGADE_SENTINEL(mybb);
             b = APR_BUCKET_NEXT(b)) {
            if (APR_BUCKET_IS_METADATA(b)) {
                /*
                 * we should NEVER see this, because we should never
                 * be passed any, but "handle" it just in case.
                 */
                continue;
            }
            if (apr_bucket_read(b, &buff, &bytes, APR_BLOCK_READ)
                    == APR_SUCCESS) {
                int have_match = 0;
                vb.strlen = 0;
                if (script->pattern) {
                    const char *repl;
                    /*
                     * space_left counts how many bytes we have left until the
                     * line length reaches AP_SUBST_MAX_LINE_LENGTH.
                     */
                    apr_size_t space_left = AP_SUBST_MAX_LINE_LENGTH;
                    apr_size_t repl_len = strlen(script->replacement);
                    while ((repl = apr_strmatch(script->pattern, buff, bytes)))
                    {
                        have_match = 1;
                        /* get offset into buff for pattern */
                        len = (apr_size_t) (repl - buff);
                        if (script->flatten && !force_quick) {
                            /*
                             * We are flattening the buckets here, meaning
                             * that we don't do the fast bucket splits.
                             * Instead we copy over what the buckets would
                             * contain and use them. This is slow, since we
                             * are constanting allocing space and copying
                             * strings.
                             */
                            if (vb.strlen + len + repl_len > AP_SUBST_MAX_LINE_LENGTH)
                                return APR_ENOMEM;
                            ap_varbuf_strmemcat(&vb, buff, len);
                            ap_varbuf_strmemcat(&vb, script->replacement, repl_len);
                        }
                        else {
                            /*
                             * The string before the match but after the
                             * previous match (if any) has length 'len'.
                             * Check if we still have space for this string and
                             * the replacement string.
                             */
                            if (space_left < len + repl_len)
                                return APR_ENOMEM;
                            space_left -= len + repl_len;
                            /*
                             * We now split off the string before the match
                             * as its own bucket, then isolate the matched
                             * string and delete it.
                             */
                            SEDRMPATBCKT(b, len, tmp_b, script->patlen);
                            /*
                             * Finally, we create a bucket that contains the
                             * replacement...
                             */
                            tmp_b = apr_bucket_transient_create(script->replacement,
                                      script->replen,
                                      f->r->connection->bucket_alloc);
                            /* ... and insert it */
                            APR_BUCKET_INSERT_BEFORE(b, tmp_b);
                        }
                        /* now we need to adjust buff for all these changes */
                        len += script->patlen;
                        bytes -= len;
                        buff += len;
                    }
                    if (have_match) {
                        if (script->flatten && !force_quick) {
                            /* XXX: we should check for AP_MAX_BUCKETS here and
                             * XXX: call ap_pass_brigade accordingly
                             */
                            char *copy = ap_varbuf_pdup(pool, &vb, NULL, 0,
                                                        buff, bytes, &len);
                            tmp_b = apr_bucket_pool_create(copy, len, pool,
                                                           f->r->connection->bucket_alloc);
                            APR_BUCKET_INSERT_BEFORE(b, tmp_b);
                            apr_bucket_delete(b);
                            b = tmp_b;
                        }
                        else {
                            /*
                             * We want the behaviour to be predictable.
                             * Therefore we try to always error out if the
                             * line length is larger than the limit,
                             * regardless of the content of the line. So,
                             * let's check if the remaining non-matching
                             * string does not exceed the limit.
                             */
                            if (space_left < b->length)
                                return APR_ENOMEM;
                        }
                    }
                }
                else if (script->regexp) {
                    int left = bytes;
                    const char *pos = buff;
                    char *repl;
                    apr_size_t space_left = AP_SUBST_MAX_LINE_LENGTH;
                    while (!ap_regexec_len(script->regexp, pos, left,
                                       AP_MAX_REG_MATCH, regm, 0)) {
                        apr_status_t rv;
                        have_match = 1;
                        if (script->flatten && !force_quick) {
                            /* copy bytes before the match */
                            if (regm[0].rm_so > 0)
                                ap_varbuf_strmemcat(&vb, pos, regm[0].rm_so);
                            /* add replacement string */
                            rv = ap_varbuf_regsub(&vb, script->replacement, pos,
                                                  AP_MAX_REG_MATCH, regm,
                                                  AP_SUBST_MAX_LINE_LENGTH - vb.strlen);
                            if (rv != APR_SUCCESS)
                                return rv;
                        }
                        else {
                            apr_size_t repl_len;
                            /* acount for string before the match */
                            if (space_left <= regm[0].rm_so)
                                return APR_ENOMEM;
                            space_left -= regm[0].rm_so;
                            rv = ap_pregsub_ex(pool, &repl,
                                               script->replacement, pos,
                                               AP_MAX_REG_MATCH, regm,
                                               space_left);
                            if (rv != APR_SUCCESS)
                                return rv;
                            repl_len = strlen(repl);
                            space_left -= repl_len;
                            len = (apr_size_t) (regm[0].rm_eo - regm[0].rm_so);
                            SEDRMPATBCKT(b, regm[0].rm_so, tmp_b, len);
                            tmp_b = apr_bucket_transient_create(repl, repl_len,
                                                f->r->connection->bucket_alloc);
                            APR_BUCKET_INSERT_BEFORE(b, tmp_b);
                        }
                        /*
                         * reset to past what we just did. pos now maps to b
                         * again
                         */
                        pos += regm[0].rm_eo;
                        left -= regm[0].rm_eo;
                    }
                    if (have_match && script->flatten && !force_quick) {
                        char *copy;
                        /* Copy result plus the part after the last match into
                         * a bucket.
                         */
                        copy = ap_varbuf_pdup(pool, &vb, NULL, 0, pos, left,
                                              &len);
                        tmp_b = apr_bucket_pool_create(copy, len, pool,
                                           f->r->connection->bucket_alloc);
                        APR_BUCKET_INSERT_BEFORE(b, tmp_b);
                        apr_bucket_delete(b);
                        b = tmp_b;
                    }
                }
                else {
                    ap_assert(0);
                    continue;
                }
            }
        }
        script++;
    }
    ap_varbuf_free(&vb);
    return APR_SUCCESS;
}