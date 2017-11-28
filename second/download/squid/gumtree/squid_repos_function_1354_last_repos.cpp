http_hdr_sc_type &operator++ (http_hdr_sc_type &aHeader)
{
    int tmp = static_cast<int>(aHeader);
    aHeader = static_cast<http_hdr_sc_type>(++tmp);
    return aHeader;
}