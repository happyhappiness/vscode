static int best_match(negotiation_state *neg, var_rec **pbest)
{
    int j;
    var_rec *best = NULL;
    float bestq = 0.0f;
    enum algorithm_results algorithm_result;

    var_rec *avail_recs = (var_rec *) neg->avail_vars->elts;

    set_default_lang_quality(neg);

    /*
     * Find the 'best' variant 
     */

    for (j = 0; j < neg->avail_vars->nelts; ++j) {
        var_rec *variant = &avail_recs[j];

        /* Find all the relevant 'quality' values from the
         * Accept... headers, and store in the variant.  This also
         * prepares for sending an Alternates header etc so we need to
         * do it even if we do not actually plan to find a best
         * variant.  
         */
        set_accept_quality(neg, variant);
        set_language_quality(neg, variant);
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