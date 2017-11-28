ClientSocketContext::Pointer
ConnStateData::getCurrentContext() const
{
    assert(this);
    return currentobject;
}