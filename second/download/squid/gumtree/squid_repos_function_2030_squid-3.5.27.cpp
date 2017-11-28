bool
SwapDir::objectSizeIsAcceptable(int64_t objsize) const
{
    // If the swapdir has no range limits, then it definitely can
    if (min_objsize <= 0 && max_objsize == -1)
        return true;

    /*
     * If the object size is -1 and the storedir has limits we
     * can't store it there.
     */
    if (objsize == -1)
        return false;

    // Else, make sure that the object size will fit.
    if (max_objsize == -1 && min_objsize <= objsize)
        return true;
    else
        return min_objsize <= objsize && max_objsize > objsize;
}