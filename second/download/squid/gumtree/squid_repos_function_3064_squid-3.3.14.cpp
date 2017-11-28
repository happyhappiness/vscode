void *
mimeEntry::operator new (size_t byteCount)
{
    return xcalloc(1, byteCount);
}