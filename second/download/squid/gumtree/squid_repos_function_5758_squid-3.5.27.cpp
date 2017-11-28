const char *
Auth::UserRequest::connLastHeader()
{
    fatal("Auth::UserRequest::connLastHeader should always be overridden by conn based auth schemes");
    return NULL;
}