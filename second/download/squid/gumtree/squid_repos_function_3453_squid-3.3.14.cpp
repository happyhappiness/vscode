void
httpStatusLineClean(HttpStatusLine * sline)
{
    HttpVersion version;
    httpStatusLineSet(sline, version, HTTP_INTERNAL_SERVER_ERROR, NULL);
}