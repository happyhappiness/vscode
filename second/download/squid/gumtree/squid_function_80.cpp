void *
AuthUserRequest::operator new (size_t byteCount)
{
    fatal ("AuthUserRequest not directly allocatable\n");
    return (void *)1;
}