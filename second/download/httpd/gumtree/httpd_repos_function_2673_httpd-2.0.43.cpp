static const char *get_locale_charset(void)
{
#if defined(HAVE_NL_LANGINFO) && defined(HAVE_CODESET)
    const char *charset;

    charset = nl_langinfo(CODESET);
    if (charset) {
        return charset;
    }
#endif

    return get_default_charset();
}