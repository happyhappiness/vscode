Http::Stream *
Http::One::Server::parseOneRequest()
{
    PROF_start(HttpServer_parseOneRequest);

    // parser is incremental. Generate new parser state if we,
    // a) dont have one already
    // b) have completed the previous request parsing already
    if (!parser_ || !parser_->needsMoreData())
        parser_ = new Http1::RequestParser(mayTunnelUnsupportedProto());

    /* Process request */
    Http::Stream *context = parseHttpRequest(this, parser_);

    PROF_stop(HttpServer_parseOneRequest);
    return context;
}