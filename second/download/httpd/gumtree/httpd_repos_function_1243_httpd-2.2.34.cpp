static void set_default_lang_quality(negotiation_state *neg)
{
    var_rec *avail_recs = (var_rec *) neg->avail_vars->elts;
    int j;

    if (!neg->dont_fiddle_headers) {
        for (j = 0; j < neg->avail_vars->nelts; ++j) {
            var_rec *variant = &avail_recs[j];
            if (variant->content_languages &&
                variant->content_languages->nelts) {
                neg->default_lang_quality = 0.0001f;
                return;
            }
        }
    }

    neg->default_lang_quality = 1.0f;
}