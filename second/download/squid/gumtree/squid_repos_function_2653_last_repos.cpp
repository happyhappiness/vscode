MemBuf *
ErrorState::BuildContent()
{
    const char *m = NULL;

    assert(page_id > ERR_NONE && page_id < error_page_count);

#if USE_ERR_LOCALES
    ErrorPageFile *localeTmpl = NULL;

    /** error_directory option in squid.conf overrides translations.
     * Custom errors are always found either in error_directory or the templates directory.
     * Otherwise locate the Accept-Language header
     */
    if (!Config.errorDirectory && page_id < ERR_MAX) {
        if (err_language && err_language != Config.errorDefaultLanguage)
            safe_free(err_language);

        localeTmpl = new ErrorPageFile(err_type_str[page_id], static_cast<err_type>(page_id));
        if (localeTmpl->loadFor(request)) {
            m = localeTmpl->text();
            assert(localeTmpl->language());
            err_language = xstrdup(localeTmpl->language());
        }
    }
#endif /* USE_ERR_LOCALES */

    /** \par
     * If client-specific error templates are not enabled or available.
     * fall back to the old style squid.conf settings.
     */
    if (!m) {
        m = error_text[page_id];
#if USE_ERR_LOCALES
        if (!Config.errorDirectory)
            err_language = Config.errorDefaultLanguage;
#endif
        debugs(4, 2, HERE << "No existing error page language negotiated for " << errorPageName(page_id) << ". Using default error file.");
    }

    MemBuf *result = ConvertText(m, true);
#if USE_ERR_LOCALES
    if (localeTmpl)
        delete localeTmpl;
#endif
    return result;
}