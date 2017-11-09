int h2_headers_are_response(h2_headers *headers)
{
    return headers->status >= 200;
}