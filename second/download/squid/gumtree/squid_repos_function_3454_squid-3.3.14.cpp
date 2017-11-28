void
httpStatusLineSet(HttpStatusLine * sline, HttpVersion version, http_status status, const char *reason)
{
    assert(sline);
    sline->protocol = AnyP::PROTO_HTTP;
    sline->version = version;
    sline->status = status;
    /* Note: no xstrdup for 'reason', assumes constant 'reasons' */
    sline->reason = reason;
}