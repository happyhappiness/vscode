static void set_accept_quality(negotiation_state *neg, var_rec *variant)
{
    int i;
    accept_rec *accept_recs;
    float q = 0.0f;
    int q_definite = 1;

    /* if no Accept: header, leave quality alone (will
     * remain at the default value of 1)
     *
     * XXX: This if is currently never true because of the effect of
     * maybe_add_default_accepts().
     */
    if (!neg->accepts) {
        if (variant->mime_type && *variant->mime_type)
            variant->definite = 0;
        return;
    }

    accept_recs = (accept_rec *) neg->accepts->elts;

    /*
     * Go through each of the ranges on the Accept: header,
     * looking for the 'best' match with this variant's
     * content-type. We use the best match's quality
     * value (from the Accept: header) for this variant's
     * mime_type_quality field.
     *
     * The best match is determined like this:
     *    type/type is better than type/ * is better than * / *
     *    if match is type/type, use the level mime param if available
     */
    for (i = 0; i < neg->accepts->nelts; ++i) {

        accept_rec *type = &accept_recs[i];
        int prev_mime_stars;

        prev_mime_stars = variant->mime_stars;

        if (!mime_match(type, variant)) {
            continue;           /* didn't match the content type at all */
        }
        else {
            /* did match - see if there were less or more stars than
             * in previous match
             */
            if (prev_mime_stars == variant->mime_stars) {
                continue;       /* more stars => not as good a match */
            }
        }

        /* If we are allowed to mess with the q-values
         * and have no explicit q= parameters in the accept header,
         * make wildcards very low, so we have a low chance
         * of ending up with them if there's something better.
         */

        if (!neg->dont_fiddle_headers && !neg->accept_q &&
            variant->mime_stars == 1) {
            q = 0.01f;
        }
        else if (!neg->dont_fiddle_headers && !neg->accept_q &&
                 variant->mime_stars == 2) {
            q = 0.02f;
        }
        else {
            q = type->quality;
        }

        q_definite = (variant->mime_stars == 3);
    }
    variant->mime_type_quality = q;
    variant->definite = variant->definite && q_definite;

}