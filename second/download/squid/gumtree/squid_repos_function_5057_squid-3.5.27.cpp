ClientSocketContext *
Http::Server::parseOneRequest(Http::ProtocolVersion &ver)
{
    ClientSocketContext *context = NULL;
    PROF_start(HttpServer_parseOneRequest);
    HttpParserInit(&parser_, in.buf.c_str(), in.buf.length());
    context = parseHttpRequest(this, &parser_, &method_, &ver);
    PROF_stop(HttpServer_parseOneRequest);
    return context;
}