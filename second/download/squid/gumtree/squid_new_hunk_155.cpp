        } else if (i < ERR_MAX) {
            /**\par
             * Index precompiled fixed template files from one of two sources:
             *  (a) default language translation directory (error_default_language)
             *  (b) admin specified custom directory (error_directory)
             */
            ErrorPageFile errTmpl(err_type_str[i], i);
            error_text[i] = errTmpl.loadDefault() ? xstrdup(errTmpl.text()) : NULL;
        } else {
            /** \par
             * Index any unknown file names used by deny_info.
             */
            ErrorDynamicPageInfo *info = ErrorDynamicPages.items[i - ERR_MAX];
            assert(info && info->id == i && info->page_name);

            const char *pg = info->page_name;
            if (info->page_redirect != HTTP_STATUS_NONE)
                pg = info->page_name +4;

            if (strchr(pg, ':') == NULL) {
                /** But only if they are not redirection URL. */
                ErrorPageFile errTmpl(pg, ERR_MAX);
                error_text[i] = errTmpl.loadDefault() ? xstrdup(errTmpl.text()) : NULL;
            }
        }
    }

    error_stylesheet.reset();

    // look for and load stylesheet into global MemBuf for it.
    if (Config.errorStylesheet) {
        ErrorPageFile tmpl("StylesSheet", ERR_MAX);
        tmpl.loadFromFile(Config.errorStylesheet);
        error_stylesheet.Printf("%s",tmpl.text());
    }

#if USE_SSL
    Ssl::errorDetailInitialize();
#endif
}

void
errorClean(void)
{
    if (error_text) {
        int i;

        for (i = ERR_NONE + 1; i < error_page_count; ++i)
            safe_free(error_text[i]);

        safe_free(error_text);
    }

    while (ErrorDynamicPages.size())
        errorDynamicPageInfoDestroy(ErrorDynamicPages.pop_back());

    error_page_count = 0;

#if USE_SSL
    Ssl::errorDetailClean();
#endif
}

/// \ingroup ErrorPageInternal
static const char *
errorFindHardText(err_type type)
{
    int i;

    for (i = 0; i < error_hard_text_count; ++i)
        if (error_hard_text[i].type == type)
            return error_hard_text[i].text;

    return NULL;
}

TemplateFile::TemplateFile(const char *name, const err_type code): silent(false), wasLoaded(false), templateName(name), templateCode(code)
{
    assert(name);
}

bool
TemplateFile::loadDefault()
{
    if (loaded()) // already loaded?
        return true;

    /** test error_directory configured location */
    if (Config.errorDirectory) {
        char path[MAXPATHLEN];
        snprintf(path, sizeof(path), "%s/%s", Config.errorDirectory, templateName.termedBuf());
        loadFromFile(path);
    }

#if USE_ERR_LOCALES
    /** test error_default_language location */
    if (!loaded() && Config.errorDefaultLanguage) {
        if (!tryLoadTemplate(Config.errorDefaultLanguage)) {
            debugs(1, (templateCode < TCP_RESET ? DBG_CRITICAL : 3), "Unable to load default error language files. Reset to backups.");
        }
    }
#endif

    /* test default location if failed (templates == English translation base templates) */
    if (!loaded()) {
        tryLoadTemplate("templates");
    }

    /* giving up if failed */
    if (!loaded()) {
        debugs(1, (templateCode < TCP_RESET ? DBG_CRITICAL : 3), "WARNING: failed to find or read error text file " << templateName);
        parse("Internal Error: Missing Template ", 33, '\0');
        parse(templateName.termedBuf(), templateName.size(), '\0');
    }

    return true;
}

bool
TemplateFile::tryLoadTemplate(const char *lang)
{
    assert(lang);

    char path[MAXPATHLEN];
    /* TODO: prep the directory path string to prevent snprintf ... */
    snprintf(path, sizeof(path), "%s/%s/%s",
             DEFAULT_SQUID_ERROR_DIR, lang, templateName.termedBuf());
    path[MAXPATHLEN-1] = '\0';

    if (loadFromFile(path))
        return true;

#if HAVE_GLOB
    if ( strlen(lang) == 2) {
        /* TODO glob the error directory for sub-dirs matching: <tag> '-*'   */
        /* use first result. */
        debugs(4,2, HERE << "wildcard fallback errors not coded yet.");
    }
#endif

    return false;
}

bool
TemplateFile::loadFromFile(const char *path)
{
    int fd;
    char buf[4096];
    ssize_t len;

    if (loaded()) // already loaded?
        return true;

    fd = file_open(path, O_RDONLY | O_TEXT);

    if (fd < 0) {
        /* with dynamic locale negotiation we may see some failures before a success. */
        if (!silent && templateCode < TCP_RESET)
            debugs(4, DBG_CRITICAL, HERE << "'" << path << "': " << xstrerror());
        wasLoaded = false;
        return wasLoaded;
    }

    while ((len = FD_READ_METHOD(fd, buf, sizeof(buf))) > 0) {
        if (!parse(buf, len, false)) {
            debugs(4, DBG_CRITICAL, HERE << " parse error while reading template file: " << path);
            wasLoaded = false;
            return wasLoaded;
        }
    }
    parse(buf, 0, true);

    if (len < 0) {
        debugs(4, DBG_CRITICAL, HERE << "failed to fully read: '" << path << "': " << xstrerror());
    }

    file_close(fd);

    wasLoaded = true;
    return wasLoaded;
}

bool strHdrAcptLangGetItem(const String &hdr, char *lang, int langLen, size_t &pos)
{
    while (pos < hdr.size()) {
        char *dt = lang;

        /* skip any initial whitespace. */
        while (pos < hdr.size() && xisspace(hdr[pos]))
            ++pos;

        /*
         * Header value format:
         *  - sequence of whitespace delimited tags
         *  - each tag may suffix with ';'.* which we can ignore.
         *  - IFF a tag contains only two characters we can wildcard ANY translations matching: <it> '-'? .*
         *    with preference given to an exact match.
         */
        bool invalid_byte = false;
        while (pos < hdr.size() && hdr[pos] != ';' && hdr[pos] != ',' && !xisspace(hdr[pos]) && dt < (lang + (langLen -1)) ) {
            if (!invalid_byte) {
#if USE_HTTP_VIOLATIONS
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
                    ++dt; // move to next destination byte.
            }
            ++pos;
        }
        *dt = '\0'; // nul-terminated the filename content string before system use.
        ++dt;

        // if we terminated the tag on garbage or ';' we need to skip to the next ',' or end of header.
        while (pos < hdr.size() && hdr[pos] != ',')
            ++pos;

        if (pos < hdr.size() && hdr[pos] == ',')
            ++pos;

        debugs(4, 9, HERE << "STATE: dt='" << dt << "', lang='" << lang << "', pos=" << pos << ", buf='" << ((pos < hdr.size()) ? hdr.substr(pos,hdr.size()) : "") << "'");

        /* if we found anything we might use, try it. */
        if (*lang != '\0' && !invalid_byte)
            return true;
    }
    return false;
}

bool
TemplateFile::loadFor(HttpRequest *request)
{
    String hdr;

#if USE_ERR_LOCALES
    if (loaded()) // already loaded?
        return true;

    if (!request || !request->header.getList(HDR_ACCEPT_LANGUAGE, &hdr) )
        return false;

    char lang[256];
    size_t pos = 0; // current parsing position in header string

    debugs(4, 6, HERE << "Testing Header: '" << hdr << "'");

    while ( strHdrAcptLangGetItem(hdr, lang, 256, pos) ) {

        /* wildcard uses the configured default language */
        if (lang[0] == '*' && lang[1] == '\0') {
            debugs(4, 6, HERE << "Found language '" << lang << "'. Using configured default.");
            return false;
        }

        debugs(4, 6, HERE << "Found language '" << lang << "', testing for available template");

        if (tryLoadTemplate(lang)) {
            /* store the language we found for the Content-Language reply header */
            errLanguage = lang;
            break;
        } else if (Config.errorLogMissingLanguages) {
            debugs(4, DBG_IMPORTANT, "WARNING: Error Pages Missing Language: " << lang);
        }
    }
#endif

    return loaded();
}

/// \ingroup ErrorPageInternal
static ErrorDynamicPageInfo *
errorDynamicPageInfoCreate(int id, const char *page_name)
{
    ErrorDynamicPageInfo *info = new ErrorDynamicPageInfo;
    info->id = id;
    info->page_name = xstrdup(page_name);
    info->page_redirect = static_cast<http_status>(atoi(page_name));

    /* WARNING on redirection status:
     * 2xx are permitted, but not documented officially.
     * - might be useful for serving static files (PAC etc) in special cases
     * 3xx require a URL suitable for Location: header.
     * - the current design does not allow for a Location: URI as well as a local file template
     *   although this possibility is explicitly permitted in the specs.
     * 4xx-5xx require a local file template.
     * - sending Location: on these codes with no body is invalid by the specs.
     * - current result is Squid crashing or XSS problems as dynamic deny_info load random disk files.
     * - a future redesign of the file loading may result in loading remote objects sent inline as local body.
     */
    if (info->page_redirect == HTTP_STATUS_NONE)
        ; // special case okay.
    else if (info->page_redirect < 200 || info->page_redirect > 599) {
        // out of range
        debugs(0, DBG_CRITICAL, "FATAL: status " << info->page_redirect << " is not valid on '" << page_name << "'");
        self_destruct();
    } else if ( /* >= 200 && */ info->page_redirect < 300 && strchr(&(page_name[4]), ':')) {
        // 2xx require a local template file
        debugs(0, DBG_CRITICAL, "FATAL: status " << info->page_redirect << " requires a template on '" << page_name << "'");
        self_destruct();
    } else if (info->page_redirect >= 300 && info->page_redirect <= 399 && !strchr(&(page_name[4]), ':')) {
        // 3xx require an absolute URL
        debugs(0, DBG_CRITICAL, "FATAL: status " << info->page_redirect << " requires a URL on '" << page_name << "'");
        self_destruct();
    } else if (info->page_redirect >= 400 /* && <= 599 */ && strchr(&(page_name[4]), ':')) {
        // 4xx/5xx require a local template file
        debugs(0, DBG_CRITICAL, "FATAL: status " << info->page_redirect << " requires a template on '" << page_name << "'");
        self_destruct();
    }
    // else okay.

    return info;
}

/// \ingroup ErrorPageInternal
static void
errorDynamicPageInfoDestroy(ErrorDynamicPageInfo * info)
