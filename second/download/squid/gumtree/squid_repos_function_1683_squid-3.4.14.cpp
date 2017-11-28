http_hdr_sc_type &operator++ (http_hdr_sc_type &aHeader)
{
    int tmp = (int)aHeader;
    aHeader = (http_hdr_sc_type)(++tmp);
    return aHeader;
}