void *
ChildVirtual::operator new(size_t byteCount)
{
    Calls.recordNew();
    return ::operator new (byteCount);
}