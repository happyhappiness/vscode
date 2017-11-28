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