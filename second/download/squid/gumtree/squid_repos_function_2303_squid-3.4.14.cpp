void
MemObject::unlinkRequest()
{
    HTTPMSGUNLOCK(request);
}