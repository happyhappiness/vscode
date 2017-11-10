static int is_variant_better(negotiation_state *neg, var_rec *variant,
                             var_rec *best, float *p_bestq)
{
    float bestq = *p_bestq, q;
    int levcmp;

    /* For non-transparent negotiation, server can choose how
     * to handle the negotiation. We'll use the following in
     * order: content-type, language, content-type level, charset,
     * content encoding, content length.
     *
     * For each check, we have three possible outcomes:
     *   This variant is worse than current best: return 0
     *   This variant is better than the current best:
     *          assign this variant's q to *p_bestq, and return 1
     *   This variant is just as desirable as the current best:
     *          drop through to the next test.
     *
     * This code is written in this long-winded way to allow future
     * customisation, either by the addition of additional
     * checks, or to allow the order of the checks to be determined
     * by configuration options (e.g. we might prefer to check
     * language quality _before_ content type).
     */

    /* First though, eliminate this variant if it is not
     * acceptable by type, charset, encoding or language.
     */

#ifdef NEG_DEBUG
    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
           "Variant: file=%s type=%s lang=%s sourceq=%1.3f "
           "mimeq=%1.3f langq=%1.3f langidx=%d charq=%1.3f encq=%1.3f ",
            (variant->file_name ? variant->file_name : ""),
            (variant->mime_type ? variant->mime_type : ""),
            (variant->content_languages
             ? apr_array_pstrcat(neg->pool, variant->content_languages, ',')
             : ""),
            variant->source_quality,
            variant->mime_type_quality,
            variant->lang_quality,
            variant->lang_index,
            variant->charset_quality,
            variant->encoding_quality);
#endif

    if (variant->encoding_quality == 0.0f ||
        variant->lang_quality == 0.0f ||
        variant->source_quality == 0.0f ||
        variant->charset_quality == 0.0f ||
        variant->mime_type_quality == 0.0f) {
        return 0;               /* don't consider unacceptables */
    }

    q = variant->mime_type_quality * variant->source_quality;
    if (q == 0.0 || q < bestq) {
        return 0;
    }
    if (q > bestq || !best) {
        *p_bestq = q;
        return 1;
    }

    /* language */
    if (variant->lang_quality < best->lang_quality) {
        return 0;
    }
    if (variant->lang_quality > best->lang_quality) {
        *p_bestq = q;
        return 1;
    }

    /* if language qualities were equal, try the LanguagePriority stuff */
    if (best->lang_index != -1 &&
        (variant->lang_index == -1 || variant->lang_index > best->lang_index)) {
        return 0;
    }
    if (variant->lang_index != -1 &&
        (best->lang_index == -1 || variant->lang_index < best->lang_index)) {
        *p_bestq = q;
        return 1;
    }

    /* content-type level (sometimes used with text/html, though we
     * support it on other types too)
     */
    levcmp = level_cmp(variant, best);
    if (levcmp == -1) {
        return 0;
    }
    if (levcmp == 1) {
        *p_bestq = q;
        return 1;
    }

    /* charset */
    if (variant->charset_quality < best->charset_quality) {
        return 0;
    }
    /* If the best variant's charset is ISO-8859-1 and this variant has
     * the same charset quality, then we prefer this variant
     */

    if (variant->charset_quality > best->charset_quality ||
        ((variant->content_charset != NULL &&
          *variant->content_charset != '\0' &&
          strcmp(variant->content_charset, "iso-8859-1") != 0) &&
         (best->content_charset == NULL ||
          *best->content_charset == '\0' ||
          strcmp(best->content_charset, "iso-8859-1") == 0))) {
        *p_bestq = q;
        return 1;
    }

    /* Prefer the highest value for encoding_quality.
     */
    if (variant->encoding_quality < best->encoding_quality) {
       return 0;
    }
    if (variant->encoding_quality > best->encoding