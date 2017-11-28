void
Auth::Basic::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, http_hdr_type hdrType, HttpRequest * request)
{
    if (authenticateProgram) {
        debugs(29, 9, HERE << "Sending type:" << hdrType << " header: 'Basic realm=\"" << basicAuthRealm << "\"'");
        httpHeaderPutStrf(&rep->header, hdrType, "Basic realm=\"%s\"", basicAuthRealm);
    }
}