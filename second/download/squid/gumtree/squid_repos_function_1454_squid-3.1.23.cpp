bool
SwapDir::optionMaxSizeParse(char const *option, const char *value, int isaReconfig)
{
    if (strcmp(option, "max-size") != 0)
        return false;

    if (!value)
        self_destruct();

    int64_t size = strtoll(value, NULL, 10);

    if (isaReconfig && max_objsize != size)
        debugs(3, 1, "Cache dir '" << path << "' max object size now " << size);

    max_objsize = size;

    return true;
}