void *
Auth::UserRequest::operator new (size_t byteCount)
{
    fatal("Auth::UserRequest not directly allocatable\n");
    return (void *)1;
}