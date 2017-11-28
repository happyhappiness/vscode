void
Auth::Basic::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, http_hdr_type hdrType, HttpRequest * request)
{
    if (authenticateProgram) {
        debugs(29, 9, "Sending type:" << hdrType << " header: 'Basic realm=\"" << realm << "\"'");
        httpHeaderPutStrf(&rep->header, hdrType, "Basic realm=\"" SQUIDSBUFPH "\"", SQUIDSBUFPRINT(realm));
    }
}