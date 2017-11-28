static int
errorPageId(const char *page_name)
{
    for (int i = 0; i < ERR_MAX; i++) {
        if (strcmp(err_type_str[i], page_name) == 0)
            return i;
    }

    for (size_t j = 0; j < ErrorDynamicPages.size(); j++) {
        if (strcmp(ErrorDynamicPages.items[j]->page_name, page_name) == 0)
            return j + ERR_MAX;
    }

    return ERR_NONE;
}