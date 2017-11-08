static const char *handle_special_names(const char *page, apr_pool_t *pool)
{
    if (page == APR_DEFAULT_CHARSET) {
        return apr_os_default_encoding(pool);
    }
    else if (page == APR_LOCALE_CHARSET) {
        return apr_os_locale_encoding(pool);
    }
    else {
        return page;
    }
}