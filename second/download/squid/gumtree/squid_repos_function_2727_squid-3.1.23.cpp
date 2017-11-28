http_hdr_type &operator++ (http_hdr_type &aHeader)
{
    int tmp = (int)aHeader;
    aHeader = (http_hdr_type)(++tmp);
    return aHeader;
}