void
AuthUserRequest::operator delete (void *address)
{
    fatal ("AuthUserRequest child failed to override operator delete\n");
}