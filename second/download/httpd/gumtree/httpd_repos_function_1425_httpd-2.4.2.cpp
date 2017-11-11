static void set_charset_quality(negotiation_state *neg, var_rec *variant)
{
    int i;
    accept_rec *accept_recs;
    const char *charset = variant->content_charset;
    accept_rec *star = NULL;

    /* if no Accept-Charset: header, leave quality alone (will
     * remain at the default value of 1)
     */
    if (!neg->accept_charsets) {
        if (charset && *charset)
            variant->definite = 0;
        return;
    }

    accept_recs = (accept_rec *) neg->accept_charsets->elts;

    if (charset == NULL || !*charset) {
        /* Charset of variant not known */

        /* if not a text / * type, leave quality alone */
        if (!(!strncmp(variant->mime_type, "text/", 5)
              || !strcmp(variant->mime_type, INCLUDES_MAGIC_TYPE)
              || !strcmp(variant->mime_type, INCLUDES_MAGIC_TYPE3)
              ))
            return;

        /* Don't go guessing if we are in strict header mode,
         * e.g. when running the rvsa, as any guess won't be reflected
         * in the variant list or content-location headers.
         */
        if (neg->dont_fiddle_headers)
            return;

        charset = "iso-8859-1"; /* The default charset for HTTP text types */
    }

    /*
     * Go through each of the items on the Accept-Charset header,
     * looking for a match with this variant's charset. If none
     * match, charset is unacceptable, so set quality to 0.
     */
    for (i = 0; i < neg->accept_charsets->nelts; ++i) {

        accept_rec *type = &accept_recs[i];

        if (!strcmp(type->name, charset)) {
            variant->charset_quality = type->quality;
            return;
        }
        else if (strcmp(type->name, "*") == 0) {
            star = type;
        }
    }
    /* No explicit match */
    if (star) {
        variant->charset_quality = star->quality;
        variant->definite = 0;
        return;
    }
    /* If this variant is in charset iso-8859-1, the default is 1.0 */
    if (strcmp(charset, "iso-8859-1") == 0) {
        variant->charset_quality = 1.0f;
    }
    else {
        variant->charset_quality = 0.0f;
    }
}