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