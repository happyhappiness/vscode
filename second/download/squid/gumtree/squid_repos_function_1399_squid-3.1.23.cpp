void
HttpRequestMethod::AddExtension(const char *mstr)
{
#if 0 /* obsolete now that we have METHOD_OTHER always enabled */
    _method_t method = METHOD_NONE;

    for (++method; method < METHOD_ENUM_END; ++method) {
        if (0 == strcmp(mstr, RequestMethodStr[method])) {
            debugs(23, 2, "Extension method '" << mstr << "' already exists");
            return;
        }

        if (0 != strncmp("%EXT", RequestMethodStr[method], 4))
            continue;

        /* Don't free statically allocated "%EXTnn" string */
        RequestMethodStr[method] = xstrdup(mstr);

        debugs(23, 1, "Extension method '" << mstr << "' added, enum=" << method);

        return;
    }

    debugs(23, 1, "WARNING: Could not add new extension method '" << mstr << "' due to lack of array space");
#endif
}