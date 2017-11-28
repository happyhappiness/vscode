int
httpReqHdrManglersConfigured()
{
    for (int i = 0; i < HDR_ENUM_END; i++) {
        if (NULL != Config.request_header_access[i].access_list)
            return 1;
    }

    return 0;
}