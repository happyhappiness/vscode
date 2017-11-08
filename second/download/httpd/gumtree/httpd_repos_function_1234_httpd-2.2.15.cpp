static int variant_has_language(var_rec *variant, const char *lang)
{
    int j, max;

    /* fast exit */
    if (   !lang
        || !variant->content_languages
        || !(max = variant->content_languages->nelts)) {
        return 0;
    }

    for (j = 0; j < max; ++j) {
        if (!strcmp(lang,
                    ((char **) (variant->content_languages->elts))[j])) {
            return 1;
        }
    }

    return 0;
}