void
Auth::Basic::Config::fixHeader(Auth::UserRequest::Pointer, HttpReply *rep, Http::HdrType hdrType, HttpRequest *)
{
    if (authenticateProgram) {
        debugs(29, 9, "Sending type:" << hdrType << " header: 'Basic realm=\"" << realm << "\"'");
        httpHeaderPutStrf(&rep->header, hdrType, "Basic realm=\"" SQUIDSBUFPH "\"", SQUIDSBUFPRINT(realm));
    }
}