void
BodyPipe::checkIn(Checkout &checkout)
{
    assert(isCheckedOut);
    isCheckedOut = false;
    const size_t currentSize = theBuf.contentSize();
    if (checkout.checkedOutSize > currentSize)
        postConsume(checkout.checkedOutSize - currentSize);
    else if (checkout.checkedOutSize < currentSize)
        postAppend(currentSize - checkout.checkedOutSize);
}