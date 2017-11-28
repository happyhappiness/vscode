void
DelayId::bytesIn(int qty)
{
    if (! (*this))
        return;

    if (markedAsNoDelay)
        return;

    assert ((unsigned short)(pool() - 1) != 0xFFFF);

    if (compositeId != NULL)
        compositeId->bytesIn(qty);
}