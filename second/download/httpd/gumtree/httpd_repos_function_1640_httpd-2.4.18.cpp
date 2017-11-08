static int is_variant_better_rvsa(negotiation_state *neg, var_rec *variant,
                                  var_rec *best, float *p_bestq)
{
    float bestq = *p_bestq, q;

    /* TCN does not cover negotiation on content-encoding.  For now,
     * we ignore the encoding unless it was explicitly excluded.
     */
    if (variant->encoding_quality == 0.0f)
        return 0;

    q = variant->mime_type_quality *
        variant->source_quality *
        variant->charset_quality *
        variant->lang_quality;

   /* RFC 2296 calls for the result to be rounded to 5 decimal places,
    * but we don't do that because it serves no useful purpose other
    * than to ensure that a remote algorithm operates on the same
    * precision as ours.  That is silly, since what we obviously want
    * is for the algorithm to operate on the best available precision
    * regardless of who runs it.  Since the above calculation may
    * result in significant variance at 1e-12, rounding would be bogus.
    */

#ifdef NEG_DEBUG
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, APLOGNO(00688)
           "Variant: file=%s type=%s lang=%s sourceq=%1.3f "
           "mimeq=%1.3f langq=%1.3f charq=%1.3f encq=%1.3f "
           "q=%1.5f definite=%d",
            (variant->file_name ? variant->file_name : ""),
            (variant->mime_type ? variant->mime_type : ""),
            (variant->content_languages
             ? apr_array_pstrcat(neg->pool, variant->content_languages, ',')
             : ""),
            variant->source_quality,
            variant->mime_type_quality,
            variant->lang_quality,
            variant->charset_quality,
            variant->encoding_quality,
            q,
            variant->definite);
#endif

    if (q <= 0.0f) {
        return 0;
    }
    if (q > bestq) {
        *p_bestq = q;
        return 1;
    }
    if (q == bestq) {
        /* If the best variant's encoding is of lesser quality than
         * this variant, then we prefer this variant
         */
        if (variant->encoding_quality > best->encoding_quality) {
            *p_bestq = q;
            return 1;
        }
    }
    return 0;
}