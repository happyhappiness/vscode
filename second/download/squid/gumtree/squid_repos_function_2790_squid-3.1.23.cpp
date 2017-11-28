http_hdr_type
httpHeaderIdByName(const char *name, size_t name_len, const HttpHeaderFieldInfo * info, int end)
{
    if (name_len > 0) {
        for (int i = 0; i < end; ++i) {
            if (name_len != info[i].name.size())
                continue;

            if (!strncasecmp(name, info[i].name.termedBuf(), name_len))
                return info[i].id;
        }
    }

    return HDR_BAD_HDR;
}