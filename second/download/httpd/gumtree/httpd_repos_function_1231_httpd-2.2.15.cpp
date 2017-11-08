static void set_encoding_quality(negotiation_state *neg, var_rec *variant)
{
    accept_rec *accept_recs;
    const char *enc = variant->content_encoding;
    accept_rec *star = NULL;
    float value_if_not_found = 0.0f;
    int i;

    if (!neg->accept_encodings) {
        /* We had no Accept-Encoding header, assume that all
         * encodings are acceptable with a low quality,
         * but we prefer no encoding if available.
         */
        if (!enc || is_identity_encoding(enc))
            variant->encoding_quality = 1.0f;
        else
            variant->encoding_quality = 0.5f;

        return;
    }

    if (!enc || is_identity_encoding(enc)) {
        enc = "identity";
        value_if_not_found = 0.0001f;
    }

    accept_recs = (accept_rec *) neg->accept_encodings->elts;

    /* Go through each of the encodings on the Accept-Encoding: header,
     * looking for a match with our encoding. x- prefixes are ignored.
     */
    if (enc[0] == 'x' && enc[1] == '-') {
        enc += 2;
    }
    for (i = 0; i < neg->accept_encodings->nelts; ++i) {

        char *name = accept_recs[i].name;

        if (name[0] == 'x' && name[1] == '-') {
            name += 2;
        }

        if (!strcmp(name, enc)) {
            variant->encoding_quality = accept_recs[i].quality;
            return;
        }

        if (strcmp(name, "*") == 0) {
            star = &accept_recs[i];
        }

    }
    /* No explicit match */
    if (star) {
        variant->encoding_quality = star->quality;
        return;
    }

    /* Encoding not found on Accept-Encoding: header, so it is
     * _not_ acceptable unless it is the identity (no encoding)
     */
    variant->encoding_quality = value_if_not_found;
}