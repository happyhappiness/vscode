void
HttpParser::clear()
{
    state = HTTP_PARSE_NONE;
    request_parse_status = HTTP_STATUS_NONE;
    buf = NULL;
    bufsiz = 0;
    req.start = req.end = -1;
    hdr_start = hdr_end = -1;
    req.m_start = req.m_end = -1;
    req.u_start = req.u_end = -1;
    req.v_start = req.v_end = -1;
    req.v_maj = req.v_min = 0;
}