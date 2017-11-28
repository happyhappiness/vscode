void
errorClean(void)
{
    if (error_text) {
        int i;

        for (i = ERR_NONE + 1; i < error_page_count; ++i)
            safe_free(error_text[i]);

        safe_free(error_text);
    }

    while (!ErrorDynamicPages.empty()) {
        errorDynamicPageInfoDestroy(ErrorDynamicPages.back());
        ErrorDynamicPages.pop_back();
    }

    error_page_count = 0;

#if USE_OPENSSL
    Ssl::errorDetailClean();
#endif
}