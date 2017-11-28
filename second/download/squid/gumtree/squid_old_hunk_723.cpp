Auth::UserRequest::operator delete (void *address)
{
    fatal("Auth::UserRequest child failed to override operator delete\n");
}

Auth::UserRequest::UserRequest():
        _auth_user(NULL),
        message(NULL),
        lastReply(AUTH_ACL_CANNOT_AUTHENTICATE)
{
    debugs(29, 5, HERE << "initialised request " << this);
}

Auth::UserRequest::~UserRequest()
{
