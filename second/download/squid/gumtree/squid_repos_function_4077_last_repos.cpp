void *
ACLIP::operator new (size_t)
{
    fatal ("ACLIP::operator new: unused");
    return (void *)1;
}