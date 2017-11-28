void
httpStatusLineInit(HttpStatusLine * sline)
{
    HttpVersion version;
    httpStatusLineSet(sline, version, HTTP_STATUS_NONE, NULL);
}