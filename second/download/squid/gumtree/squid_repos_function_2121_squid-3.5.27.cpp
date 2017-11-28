MemBuf &
BodyPipe::checkOut()
{
    assert(!isCheckedOut);
    isCheckedOut = true;
    return theBuf;
}