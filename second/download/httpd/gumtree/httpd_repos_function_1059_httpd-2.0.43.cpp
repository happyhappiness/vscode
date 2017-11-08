static void set_language_quality(negotiation_state *neg, var_rec *variant)
{
    int forcepriority = neg->conf->forcelangpriority;
    if (forcepriority == FLP_UNDEF) {
        forcepriority = FLP_DEFAULT;
    }

    if (!variant->content_languages || !variant->content_languages->nelts) {
        /* This variant has no content-language, so use the default
         * quality factor for variants with no content-language
         * (previously set by set_default_lang_quality()).
         * Leave the factor alone (it remains at 1.0) when we may not fiddle
         * with the headers.
         */
        if (!neg->dont_fiddle_headers) {
            variant->lang_quality = neg->default_lang_quality;
        }
        if (!neg->accept_langs) {
            return;             /* no accept-language header */
        }
        return;
    }
    else {
        /* Variant has one (or more) languages.  Look for the best
         * match. We do this by going through each language on the
         * variant description looking for a match on the
         * Accept-Language header. The best match is the longest
         * matching language on the header. The final result is the
         * best q value from all the languages on the variant
         * description.
         */

        if (!neg->accept_langs) {
            /* no accept-language header makes the variant indefinite */
            variant->definite = 0;
        }
        else {    /* There is an accept-language with 0 or more items */
            accept_rec *accs = (accept_rec *) neg->accept_langs->elts;
            accept_rec *best = NULL, *star = NULL;
            accept_rec *bestthistag;
            char *lang, *p;
            float fiddle_q = 0.0f;
            int any_match_on_star = 0;
            int i, j;
            apr_size_t alen, longest_lang_range_len;

            for (j = 0; j < variant->content_languages->nelts; ++j) {
                p = NULL;
                bestthistag = NULL;
                longest_lang_range_len = 0;
                alen = 0;
                
                /* lang is the variant's language-tag, which is the one
                 * we are allowed to use the prefix of in HTTP/1.1
                 */
                lang = ((char **) (variant->content_languages->elts))[j];
                
                /* now find the best (i.e. longest) matching
                 * Accept-Language header language. We put the best match
                 * for this tag in bestthistag. We cannot update the
                 * overall best (based on q value) because the best match
                 * for this tag is the longest language item on the accept
                 * header, not necessarily the highest q.
                 */
                for (i = 0; i < neg->accept_langs->nelts; ++i) {
                    if (!strcmp(accs[i].name, "*")) {
                        if (!star) {
                            star = &accs[i];
                        }
                        continue;
                    }
                    /* Find language. We match if either the variant
                     * language tag exactly matches the language range
                     * from the accept header, or a prefix of the variant
                     * language tag up to a '-' character matches the
                     * whole of the language range in the Accept-Language
                     * header.  Note that HTTP/1.x allows any number of
                     * '-' characters in a tag or range, currently only
                     * tags with zero or one '-' characters are defined
                     * for general use (see rfc1766).
                     *  
                     * We only use language range in the Accept-Language
                     * header the best match for the variant language tag
                     * if it is longer than the previous best match.
                     */
                    
                    alen = strlen(accs[i].name);
                    
                    if ((strlen(lang) >= alen) &&
                        !strncmp(lang, accs[i].name, alen) &&
                        ((lang[alen] == 0) || (lang[alen] == '-')) ) {
                        
                        if (alen > longest_lang_range_len) {
                            longest_lang_range_len = alen;
                            bestthistag = &accs[i];
                        }
                    }
                    
                    if (!bestthistag && !neg->dont_fiddle_headers) {
                        /* The next bit is a fiddle. Some browsers might
                         * be configured to send more specific language
                         * ranges than desirable. For example, an
                         * Accept-Language of en-US should never match
                         * variants with languages en or en-GB. But US
                         * English speakers might pick en-US as their
                         * language choice.  So this fiddle checks if the
                         * language range has a prefix, and if so, it
                         * matches variants which match that prefix with a
                         * priority of 0.001. So a request for en-US would
                         * match variants of types en and en-GB, but at
                         * much lower priority than matches of en-US
                         * directly, or of any other language listed on
                         * the Accept-Language header. Note that this
                         * fiddle does not handle multi-level prefixes.
                         */
                        if ((p = strchr(accs[i].name, '-'))) {
                            int plen = p - accs[i].name;

                            if (!strncmp(lang, accs[i].name, plen)) {
                                fiddle_q = 0.001f;
                            }
                        }
                    }
                }
                /* Finished looking at Accept-Language headers, the best
                 * (longest) match is in bestthistag, or NULL if no match
                 */
                if (!best ||
                    (bestthistag && bestthistag->quality > best->quality)) {
                    best = bestthistag;
                }
                
                /* See if the tag matches on a * in the Accept-Language
                 * header. If so, record this fact for later use 
                 */
                if (!bestthistag && star) {
                    any_match_on_star = 1;
                }
            }
            
            /* If one of the language tags of the variant matched on *, we
             * need to see if its q is better than that of any non-* match
             * on any other tag of the variant.  If so the * match takes
             * precedence and the overall match is not definite.
             */
            if ( any_match_on_star &&
                ((best && star->quality > best->quality) ||
                 (!best)) ) {
                best = star;
                variant->definite = 0;
            }
            
            variant->lang_quality = best ? best->quality : fiddle_q;
        }
    }

    /* Handle the ForceDefaultLanguage overrides, based on the best match
     * to LanguagePriority order.  The best match is the lowest index of 
     * any LanguagePriority match.
     */
    if (((forcepriority & FLP_PREFER) 
             && (variant->lang_index < 0))
     || ((forcepriority & FLP_FALLBACK)
             && !variant->lang_quality)) 
    {
        int bestidx = -1;
        int j;

        for (j = 0; j < variant->content_languages->nelts; ++j) 
        {
            /* lang is the variant's language-tag, which is the one
             * we are allowed to use the prefix of in HTTP/1.1
             */
            char *lang = ((char **) (variant->content_languages->elts))[j];
            int idx = -1;
        
            /* If we wish to fallback or 
             * we use our own LanguagePriority index.
             */
            idx = find_lang_index(neg->conf->language_priority, lang);
            if ((idx >= 0) && ((bestidx == -1) || (idx < bestidx))) {
                bestidx = idx;
            }
        }

        if (bestidx >= 0) {
            if (variant->lang_quality) {
                if (forcepriority & FLP_PREFER) {
                    variant->lang_index = bestidx;
                }
            }
            else {
                if (forcepriority & FLP_FALLBACK) {
                    variant->lang_index = bestidx;
                    variant->lang_quality = .0001f;
                    variant->definite = 0;
                }
            }
        }
    }
    return;
}