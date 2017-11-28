static void
errorDynamicPageInfoDestroy(ErrorDynamicPageInfo * info)
{
    assert(info);
    safe_free(info->page_name);
    delete info;
}