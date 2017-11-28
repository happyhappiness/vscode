const char *
httpHeaderNameById(int id)
{
    if (!Headers)
        Headers = httpHeaderBuildFieldsInfo(HeadersAttrs, HDR_ENUM_END);

    assert(id >= 0 && id < HDR_ENUM_END);

    return Headers[id].name.termedBuf();
}