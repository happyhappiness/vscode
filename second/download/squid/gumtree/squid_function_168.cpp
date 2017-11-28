void
errorInitialize(void)
{
    err_type i;
    const char *text;
    error_page_count = ERR_MAX + ErrorDynamicPages.size();
    error_text = static_cast<char **>(xcalloc(error_page_count, sizeof(char *)));

    for (i = ERR_NONE, ++i; i < error_page_count; ++i) {
        safe_free(error_text[i]);

        if ((text = errorFindHardText(i))) {
            /**\par
             * Index any hard-coded error text into defaults.
             */
            error_text[i] = xstrdup(text);

        } else if (i < ERR_MAX) {
            /**\par
             * Index precompiled fixed template files from one of two sources:
             *  (a) default language translation directory (error_default_language)
             *  (b) admin specified custom directory (error_directory)
             */
            error_text[i] = errorLoadText(err_type_str[i]);

        } else {
            /** \par
             * Index any unknown file names used by deny_info.
             */
            ErrorDynamicPageInfo *info = ErrorDynamicPages.items[i - ERR_MAX];
            assert(info && info->id == i && info->page_name);

            if (strchr(info->page_name, ':') == NULL) {
                /** But only if they are not redirection URL. */
                error_text[i] = errorLoadText(info->page_name);
            }
        }
    }

    error_stylesheet.reset();

    // look for and load stylesheet into global MemBuf for it.
    if (Config.errorStylesheet) {
        char *temp = errorTryLoadText(Config.errorStylesheet,NULL);
        if (temp) {
            error_stylesheet.Printf("%s",temp);
            safe_free(temp);
        }
    }
}