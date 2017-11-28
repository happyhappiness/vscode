void
Auth::UserRequest::start(HttpRequest *request, AccessLogEntry::Pointer &al, AUTHCB * handler, void *data)
{
    assert(handler);
    assert(data);
    debugs(29, 9, this);
    startHelperLookup(request, al, handler, data);
}