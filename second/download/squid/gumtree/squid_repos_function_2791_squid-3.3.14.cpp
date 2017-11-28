http_hdr_type
httpHeaderIdByNameDef(const char *name, int name_len)
{
    if (!Headers)
        Headers = httpHeaderBuildFieldsInfo(HeadersAttrs, HDR_ENUM_END);

    return httpHeaderIdByName(name, name_len, Headers, HDR_ENUM_END);
}