static char *find_desc(autoindex_config_rec *dcfg, const char *filename_full)
{
    int i;
    ai_desc_t *list = (ai_desc_t *) dcfg->desc_list->elts;
    const char *filename_only;
    const char *filename;

    /*
     * If the filename includes a path, extract just the name itself
     * for the simple matches.
     */
    if ((filename_only = ap_strrchr_c(filename_full, '/')) == NULL) {
        filename_only = filename_full;
    }
    else {
        filename_only++;
    }
    for (i = 0; i < dcfg->desc_list->nelts; ++i) {
        ai_desc_t *tuple = &list[i];
        int found;

        /*
         * Only use the full-path filename if the pattern contains '/'s.
         */
        filename = (tuple->full_path) ? filename_full : filename_only;
        /*
         * Make the comparison using the cheapest method; only do
         * wildcard checking if we must.
         */
        if (tuple->wildcards) {
            found = (apr_fnmatch(tuple->pattern, filename, MATCH_FLAGS) == 0);
        }
        else {
            found = (ap_strstr_c(filename, tuple->pattern) != NULL);
        }
        if (found) {
            return tuple->description;
        }
    }
    return NULL;
}