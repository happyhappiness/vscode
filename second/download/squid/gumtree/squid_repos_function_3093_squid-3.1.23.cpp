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