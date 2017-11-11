static const char *dav_fs_get_supportedlock(const dav_resource *resource)
{
    static const char supported[] = DEBUG_CR
        "<D:lockentry>" DEBUG_CR
        "<D:lockscope><D:exclusive/></D:lockscope>" DEBUG_CR
        "<D:locktype><D:write/></D:locktype>" DEBUG_CR
        "</D:lockentry>" DEBUG_CR
        "<D:lockentry>" DEBUG_CR
        "<D:lockscope><D:shared/></D:lockscope>" DEBUG_CR
        "<D:locktype><D:write/></D:locktype>" DEBUG_CR
        "</D:lockentry>" DEBUG_CR;

    return supported;
}