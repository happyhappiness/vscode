void
BodyPipe::undoCheckOut(Checkout &checkout)
{
    assert(isCheckedOut);
    const size_t currentSize = theBuf.contentSize();
    // We can only undo if size did not change, and even that carries
    // some risk. If this becomes a problem, the code checking out
    // raw buffers should always check them in (possibly unchanged)
    // instead of relying on the automated undo mechanism of Checkout.
    // The code can always use a temporary buffer to accomplish that.
    Must(checkout.checkedOutSize == currentSize);
}