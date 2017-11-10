static int best_match(negotiation_state *neg, var_rec **pbest)
{
    int j;
    var_rec *best;
    float bestq = 0.0f;
    enum algorithm_results algorithm_result;
    int may_discard = 0;

    var_rec *avail_recs = (var_rec *) neg->avail_vars->elts;

    /* fetch request dependent variables
     * prefer-language: prefer a certain language.
     */
    const char *preferred_language = apr_table_get(neg->r->subprocess_env,
                                                   "prefer-language");

    /* no-gzip: do not send encoded documents */
    if (apr_table_get(neg->r->subprocess_env, "no-gzip")) {
        may_discard = DISCARD_ALL_ENCODINGS;
    }

    /* gzip-only-text/html: send encoded documents only
     * if they are text/html. (no-gzip has a higher priority).
     */
    else {
        const char *env_value = apr_table_get(neg->r->subprocess_env,
                                              "gzip-only-text/html");

        if (env_value && !strcmp(env_value, "1")) {
            may_discard = DISCARD_ALL_BUT_HTML;
        }
    }

    set_default_lang_quality(neg);

    /*
     * Find the 'best' variant
     * We run the loop possibly twice: if "prefer-language"
     * environment variable is set but we did not find an appropriate
     * best variant. In that case forget the preferred language and
     * negotiate over all variants.
     */

    do {
        best = NULL;

        for (j = 0; j < neg->avail_vars->nelts; ++j) {
            var_rec *variant = &avail_recs[j];

            /* if this variant is encoded somehow and there are special
             * variables set, we do not negotiate it. see above.
             */
            if (   may_discard
                && discard_variant_by_env(variant, may_discard)) {
                continue;
            }

            /* if a language is preferred, but the current variant
             * is not in that language, then drop it for now
             */
            if (   preferred_language
                && !variant_has_language(variant, preferred_language)) {
                continue;
            }

            /* Find all the relevant 'quality' values from the
             * Accept... headers, and store in the variant.  This also
             * prepares for sending an Alternates header etc so we need to
             * do it even if we do not actually plan to find a best
             * variant.
             */
            set_accept_quality(neg, variant);
            /* accept the preferred language, even when it's not listed within
             * the Accept-Language header
             */
            if (preferred_language) {
                variant->lang_quality = 1.0f;
                variant->definite = 1;
            }
            else {
                set_language_quality(neg, variant);
            }
            set_encoding_quality(neg, variant);
            set_charset_quality(neg, variant);

            /* Only do variant selection if we may actually choose a
             * variant for the client
             */
            if (neg->may_choose) {

                /* Now find out if this variant is better than the current
                 * best, either using the RVSA/1.0 algorithm, or Apache's
                 * internal server-driven algorithm. Presumably other
                 * server-driven algorithms are possible, and could be
                 * implemented here.
                 */

                if (neg->use_rvsa) {
                    if (is_variant_better_rvsa(neg, variant, best, &bestq)) {
                        best = variant;
                    }
                }
                else {
                    if (is_variant_better(neg, variant, best, &bestq)) {
                        best = variant;
                    }
                }
            }
        }

        /* We now either have a best variant, or no best variant */

        if (neg->use_rvsa)    {
            /* calculate result for RVSA/1.0 algorithm:
             * only a choice response if the best variant has q>0
             * and is definite
             */
            algorithm_result = (best && best->definite) && (bestq > 0) ?
                                alg_choice : alg_list;
        }
        else {
            /* calculate result for Apache negotiation algorithm */
            algorithm_result = bestq > 0 ? alg_choice : alg_list;
        }

        /* run the loop again, if the "prefer-language" got no clear result */
        if (preferred_language && (!best || algorithm_result != alg_choice)) {
            preferred_language = NULL;
            continue;
        }

        break;
    } while (1);

    /* Returning a choice response with a non-neighboring variant is a
     * protocol security error in TCN (see rfc2295).  We do *not*
     * verify here that the variant and URI are neighbors, even though
     * we may return alg_choice.  We depend on the environment (the
     * caller) to only declare the resource transparently negotiable if
     * all variants are neighbors.
     */
    *pbest = best;
    return algorithm_result;
}