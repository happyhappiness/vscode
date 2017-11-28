const char *
AuthUserRequest::connLastHeader()
{
    fatal("AuthUserRequest::connLastHeader should always be overridden by conn based auth schemes");
    return NULL;
}