static int variant_has_language(var_rec *variant, const char *lang)
{
    /* fast exit */
    if (   !lang
        || !variant->content_languages) {
        return 0;
    }

    if (ap_array_str_contains(variant->content_languages, lang)) {
        return 1;
    }

    return 0;
}