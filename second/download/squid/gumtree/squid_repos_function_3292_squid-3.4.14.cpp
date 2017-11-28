int
DelayId::bytesWanted(int minimum, int maximum) const
{
    /* unlimited */

    if (! (*this) || markedAsNoDelay)
        return max(minimum, maximum);

    /* limited */
    int nbytes = max(minimum, maximum);

    if (compositeId != NULL)
        nbytes = compositeId->bytesWanted(minimum, nbytes);

    return nbytes;
}