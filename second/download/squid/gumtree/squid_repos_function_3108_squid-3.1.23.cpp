MemBuf *
ErrorState::BuildContent()
{
    const char *m = NULL;

    assert(page_id > ERR_NONE && page_id < error_page_count);

#if USE_ERR_LOCALES
    String hdr;
    char dir[256];
    int l = 0;
    const char *freePage = NULL;

    /** error_directory option in squid.conf overrides translations.
     * Custom errors are always found either in error_directory or the templates directory.
     * Otherwise locate the Accept-Language header
     */
    if (!Config.errorDirectory && page_id < ERR_MAX && request && request->header.getList(HDR_ACCEPT_LANGUAGE, &hdr) ) {

        size_t pos = 0; // current parsing position in header string
        char *reset = NULL; // where to reset the p pointer for each new tag file
        char *dt = NULL;

        /* prep the directory path string to prevent snprintf ... */
        l = strlen(DEFAULT_SQUID_ERROR_DIR);
        memcpy(dir, DEFAULT_SQUID_ERROR_DIR, l);
        dir[ l++ ] = '/';
        reset = dt = dir + l;

        debugs(4, 6, HERE << "Testing Header: '" << hdr << "'");

        while ( pos < hdr.size() ) {

            /* skip any initial whitespace. */
            while (pos < hdr.size() && xisspace(hdr[pos])) pos++;

            /*
             * Header value format:
             *  - sequence of whitespace delimited tags
             *  - each tag may suffix with ';'.* which we can ignore.
             *  - IFF a tag contains only two characters we can wildcard ANY translations matching: <it> '-'? .*
             *    with preference given to an exact match.
             */
            bool invalid_byte = false;
            while (pos < hdr.size() && hdr[pos] != ';' && hdr[pos] != ',' && !xisspace(hdr[pos]) && dt < (dir+256) ) {
                if (!invalid_byte) {
#if HTTP_VIOLATIONS
                    // if accepting violations we may as well accept some broken browsers
                    //  which may send us the right code, wrong ISO formatting.
                    if (hdr[pos] == '_')
                        *dt = '-';
                    else
#endif
                        *dt = xtolower(hdr[pos]);
                    // valid codes only contain A-Z, hyphen (-) and *
                    if (*dt != '-' && *dt != '*' && (*dt < 'a' || *dt > 'z') )
                        invalid_byte = true;
                    else
                        dt++; // move to next destination byte.
                }
                pos++;
            }
            *dt++ = '\0'; // nul-terminated the filename content string before system use.

            debugs(4, 9, HERE << "STATE: dt='" << dt << "', reset='" << reset << "', pos=" << pos << ", buf='" << ((pos < hdr.size()) ? hdr.substr(pos,hdr.size()) : "") << "'");

            /* if we found anything we might use, try it. */
            if (*reset != '\0' && !invalid_byte) {

                /* wildcard uses the configured default language */
                if (reset[0] == '*' && reset[1] == '\0') {
                    debugs(4, 6, HERE << "Found language '" << reset << "'. Using configured default.");
                    m = error_text[page_id];
                    if (!Config.errorDirectory)
                        err_language = Config.errorDefaultLanguage;
                    break;
                }

                debugs(4, 6, HERE << "Found language '" << reset << "', testing for available template in: '" << dir << "'");

                m = errorTryLoadText( err_type_str[page_id], dir, false);

                if (m) {
                    /* store the language we found for the Content-Language reply header */
                    err_language = xstrdup(reset);
                    freePage = m;
                    break;
                } else if (Config.errorLogMissingLanguages) {
                    debugs(4, DBG_IMPORTANT, "WARNING: Error Pages Missing Language: " << reset);
                }

#if HAVE_GLOB
                if ( (dt - reset) == 2) {
                    /* TODO glob the error directory for sub-dirs matching: <tag> '-*'   */
                    /* use first result. */
                    debugs(4,2, HERE << "wildcard fallback errors not coded yet.");
                }
#endif
            }

            dt = reset; // reset for next tag testing. we replace the failed name instead of cloning.

            // IFF we terminated the tag on whitespace or ';' we need to skip to the next ',' or end of header.
            while (pos < hdr.size() && hdr[pos] != ',') pos++;
            if (hdr[pos] == ',') pos++;
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
    safe_free(freePage);
#endif

    return result;
}