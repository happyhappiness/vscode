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

void
errorClean(void)
{
    if (error_text) {
        int i;

        for (i = ERR_NONE + 1; i < error_page_count; i++)
            safe_free(error_text[i]);

        safe_free(error_text);
    }

    while (ErrorDynamicPages.size())
        errorDynamicPageInfoDestroy(ErrorDynamicPages.pop_back());

    error_page_count = 0;
}

/// \ingroup ErrorPageInternal
static const char *
errorFindHardText(err_type type)
{
    int i;

    for (i = 0; i < error_hard_text_count; i++)
        if (error_hard_text[i].type == type)
            return error_hard_text[i].text;

    return NULL;
}

/**
 * \ingroup ErrorPageInternal
 *
 * Load into the in-memory error text Index a file probably available at:
 *  (a) admin specified custom directory (error_directory)
 *  (b) default language translation directory (error_default_language)
 *  (c) English sub-directory where errors should ALWAYS exist
 */
static char *
errorLoadText(const char *page_name)
{
    char *text = NULL;

    /** test error_directory configured location */
    if (Config.errorDirectory)
        text = errorTryLoadText(page_name, Config.errorDirectory);

#if USE_ERR_LOCALES
    /** test error_default_language location */
    if (!text && Config.errorDefaultLanguage) {
        char dir[256];
        snprintf(dir,256,"%s/%s", DEFAULT_SQUID_ERROR_DIR, Config.errorDefaultLanguage);
        text = errorTryLoadText(page_name, dir);
        if (!text) {
            debugs(1, DBG_CRITICAL, "Unable to load default error language files. Reset to backups.");
        }
    }
#endif

    /* test default location if failed (templates == English translation base templates) */
    if (!text) {
        text = errorTryLoadText(page_name, DEFAULT_SQUID_ERROR_DIR"/templates");
    }

    /* giving up if failed */
    if (!text)
        fatal("failed to find or read error text file.");

    return text;
}

/// \ingroup ErrorPageInternal
static char *
errorTryLoadText(const char *page_name, const char *dir, bool silent)
{
    int fd;
    char path[MAXPATHLEN];
    char buf[4096];
    char *text;
    ssize_t len;
    MemBuf textbuf;

    // maybe received compound parts, maybe an absolute page_name and no dir
    if (dir)
        snprintf(path, sizeof(path), "%s/%s", dir, page_name);
    else
        snprintf(path, sizeof(path), "%s", page_name);

    fd = file_open(path, O_RDONLY | O_TEXT);

    if (fd < 0) {
        /* with dynamic locale negotiation we may see some failures before a success. */
        if (!silent)
            debugs(4, DBG_CRITICAL, HERE << "'" << path << "': " << xstrerror());
        return NULL;
    }

    textbuf.init();

    while ((len = FD_READ_METHOD(fd, buf, sizeof(buf))) > 0) {
        textbuf.append(buf, len);
    }

    if (len < 0) {
        debugs(4, DBG_CRITICAL, HERE << "failed to fully read: '" << path << "': " << xstrerror());
    }

    file_close(fd);

    /* Shrink memory size down to exact size. MemBuf has a tencendy
     * to be rather large..
     */
    text = xstrdup(textbuf.buf);

    textbuf.clean();

    return text;
}

/// \ingroup ErrorPageInternal
static ErrorDynamicPageInfo *
errorDynamicPageInfoCreate(int id, const char *page_name)
{
    ErrorDynamicPageInfo *info = new ErrorDynamicPageInfo;
    info->id = id;
    info->page_name = xstrdup(page_name);
    return info;
}

/// \ingroup ErrorPageInternal
static void
errorDynamicPageInfoDestroy(ErrorDynamicPageInfo * info)
