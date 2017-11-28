void *
ACL::operator new (size_t byteCount)
{
    fatal ("unusable ACL::new");
    return (void *)1;
}