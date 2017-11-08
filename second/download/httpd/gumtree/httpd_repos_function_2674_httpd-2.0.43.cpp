static const char *handle_special_names(const char *page)
{
    if (page == APR_DEFAULT_CHARSET) {
        return get_default_charset();
    }
    else if (page == APR_LOCALE_CHARSET) {
        return get_locale_charset();
    }
    else {
        return page;
    }
}