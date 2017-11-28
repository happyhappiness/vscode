void *
Auth::UserRequest::operator new (size_t)
{
    fatal("Auth::UserRequest not directly allocatable\n");
    return (void *)1;
}