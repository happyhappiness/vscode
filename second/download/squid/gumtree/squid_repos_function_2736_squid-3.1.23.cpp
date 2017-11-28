int
HttpHeader::reset()
{
    http_hdr_owner_type ho;
    ho = owner;
    clean();
    *this = HttpHeader(ho);
    return 0;
}