const char *
errorPageName(int pageId)
{
    if (pageId >= ERR_NONE && pageId < ERR_MAX)     /* common case */
        return err_type_str[pageId];

    if (pageId >= ERR_MAX && pageId - ERR_MAX < (ssize_t)ErrorDynamicPages.size())
        return ErrorDynamicPages[pageId - ERR_MAX]->page_name;

    return "ERR_UNKNOWN";   /* should not happen */
}