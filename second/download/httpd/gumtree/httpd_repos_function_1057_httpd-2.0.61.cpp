static int find_lang_index(apr_array_header_t *accept_langs, char *lang)
{
    const char **alang;
    int i;

    if (!lang || !accept_langs) {
        return -1;
    }

    alang = (const char **) accept_langs->elts;

    for (i = 0; i < accept_langs->nelts; ++i) {
        if (!strncmp(lang, *alang, strlen(*alang))) {
            return i;
        }
        alang += (accept_langs->elt_size / sizeof(char*));
    }

    return -1;
}