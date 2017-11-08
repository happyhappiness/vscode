static void fill_in_header(fcgi_header *header,
                           unsigned char type,
                           apr_uint16_t request_id,
                           apr_uint16_t content_len,
                           unsigned char padding_len)
{
    header->version = FCGI_VERSION;

    header->type = type;

    header->requestIdB1 = ((request_id >> 8) & 0xff);
    header->requestIdB0 = ((request_id) & 0xff);

    header->contentLengthB1 = ((content_len >> 8) & 0xff);
    header->contentLengthB0 = ((content_len) & 0xff);

    header->paddingLength = padding_len;

    header->reserved = 0;
}