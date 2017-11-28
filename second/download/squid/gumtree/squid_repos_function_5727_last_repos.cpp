const char *
Auth::UserRequest::helperRequestKeyExtras(HttpRequest *request, AccessLogEntry::Pointer &al)
{
    if (Format::Format *reqFmt = user()->config->keyExtras) {
        static MemBuf mb;
        mb.reset();
        // We should pass AccessLogEntry as second argument ....
        Auth::UserRequest::Pointer oldReq = request->auth_user_request;
        request->auth_user_request = this;
        reqFmt->assemble(mb, al, 0);
        request->auth_user_request = oldReq;
        debugs(29, 5, "Assembled line to send :" << mb.content());
        return mb.content();
    }
    return NULL;
}