void
HttpParserInit(HttpParser *hdr, const char *buf, int bufsiz)
{
    hdr->state = 1;
    hdr->buf = buf;
    hdr->bufsiz = bufsiz;
    hdr->req_start = hdr->req_end = -1;
    hdr->hdr_start = hdr->hdr_end = -1;
    debugs(74, 5, "httpParseInit: Request buffer is " << buf);
    hdr->m_start = hdr->m_end = -1;
    hdr->u_start = hdr->u_end = -1;
    hdr->v_start = hdr->v_end = -1;
    hdr->v_maj = hdr->v_min = 0;
}