char *
mime_get_header(const char *mime, const char *name)
{
    return mime_get_header_field(mime, name, NULL);
}