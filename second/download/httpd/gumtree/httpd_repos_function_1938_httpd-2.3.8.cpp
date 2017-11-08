static void do_pattmatch(ap_filter_t *f, apr_bucket *inb,
                         apr_bucket_brigade *mybb,
                         apr_pool_t *tmp_pool)
{
    int i;
    int force_quick = 0;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
    apr_size_t bytes;
    apr_size_t len;
    apr_size_t fbytes;
    const char *buff;
    const char *repl;
    char *scratch;
    char *p;
    char *s1;
    char *s2;
    apr_bucket *b;
    apr_bucket *tmp_b;
    apr_pool_t *tpool;

    subst_dir_conf *cfg =
    (subst_dir_conf *) ap_get_module_config(f->r->per_dir_config,
                                             &substitute_module);
    subst_pattern_t *script;

    APR_BRIGADE_INSERT_TAIL(mybb, inb);
    
    script = (subst_pattern_t *) cfg->patterns->elts;
    apr_pool_create(&tpool, tmp_pool);
    scratch = NULL;
    fbytes = 0;
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
                s1 = NULL;
                if (script->pattern) {
                    while ((repl = apr_strmatch(script->pattern, buff, bytes)))
                    {
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
                            SEDSCAT(s1, s2, tmp_pool, buff, len,
                                    script->replacement);
                        }
                        else {
                            /*
                             * We now split off the stuff before the regex
                             * as its own bucket, then isolate the pattern
                             * and delete it.
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
                    if (script->flatten && s1 && !force_quick) {
                        /*
                         * we've finished looking at the bucket, so remove the
                         * old one and add in our new one
                         */
                        s2 = apr_pstrmemdup(tmp_pool, buff, bytes);
                        s1 = apr_pstrcat(tmp_pool, s1, s2, NULL);
                        tmp_b = apr_bucket_transient_create(s1, strlen(s1),
                                            f->r->connection->bucket_alloc);
                        APR_BUCKET_INSERT_BEFORE(b, tmp_b);
                        apr_bucket_delete(b);
                        b = tmp_b;
                    }

                }
                else if (script->regexp) {
                    /*
                     * we need a null terminated string here :(. To hopefully
                     * save time and memory, we don't alloc for each run
                     * through, but only if we need to have a larger chunk
                     * to save the string to. So we keep track of how much
                     * we've allocated and only re-alloc when we need it.
                     * NOTE: this screams for a macro.
                     */
                    if (!scratch || (bytes > (fbytes + 1))) {
                        fbytes = bytes + 1;
                        scratch = apr_palloc(tpool, fbytes);
                    }
                    /* reset pointer to the scratch space */
                    p = scratch;
                    memcpy(p, buff, bytes);
                    p[bytes] = '\0';
                    while (!ap_regexec(script->regexp, p,
                                       AP_MAX_REG_MATCH, regm, 0)) {
                        /* first, grab the replacement string */
                        repl = ap_pregsub(tmp_pool, script->replacement, p,
                                          AP_MAX_REG_MATCH, regm);
                        if (script->flatten && !force_quick) {
                            SEDSCAT(s1, s2, tmp_pool, p, regm[0].rm_so, repl);
                        }
                        else {
                            len = (apr_size_t) (regm[0].rm_eo - regm[0].rm_so);
                            SEDRMPATBCKT(b, regm[0].rm_so, tmp_b, len);
                            tmp_b = apr_bucket_transient_create(repl,
                                                                strlen(repl),
                                             f->r->connection->bucket_alloc);
                            APR_BUCKET_INSERT_BEFORE(b, tmp_b);
                        }
                        /*
                         * reset to past what we just did. buff now maps to b
                         * again
                         */
                        p += regm[0].rm_eo;
                    }
                    if (script->flatten && s1 && !force_quick) {
                        s1 = apr_pstrcat(tmp_pool, s1, p, NULL);
                        tmp_b = apr_bucket_transient_create(s1, strlen(s1),
                                            f->r->connection->bucket_alloc);
                        APR_BUCKET_INSERT_BEFORE(b, tmp_b);
                        apr_bucket_delete(b);
                        b = tmp_b;
                    }

                }
                else {
                    /* huh? */
                    continue;
                }
            }
        }
        script++;
    }

    apr_pool_destroy(tpool);

    return;
}