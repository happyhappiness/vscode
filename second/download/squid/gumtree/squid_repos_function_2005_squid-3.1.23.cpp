void
HttpStateData::truncateVirginBody()
{
    assert(flags.headers_parsed);

    HttpReply *vrep = virginReply();
    int64_t clen = -1;
    if (!vrep->expectingBody(request->method, clen) || clen < 0)
        return; // no body or a body of unknown size, including chunked

    const int64_t body_bytes_read = reply_bytes_read - header_bytes_read;
    if (body_bytes_read - body_bytes_truncated <= clen)
        return; // we did not read too much or already took care of the extras

    if (const int64_t extras = body_bytes_read - body_bytes_truncated - clen) {
        // server sent more that the advertised content length
        debugs(11,5, HERE << "body_bytes_read=" << body_bytes_read <<
               " clen=" << clen << '/' << vrep->content_length <<
               " body_bytes_truncated=" << body_bytes_truncated << '+' << extras);

        readBuf->truncate(extras);
        body_bytes_truncated += extras;
    }
}