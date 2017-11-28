bool
SwapDir::objectSizeIsAcceptable(int64_t objsize) const
{
    /*
     * If the swapdir's max_obj_size is -1, then it definitely can
     */

    if (max_objsize == -1)
        return true;

    /*
     * If the object size is -1, then if the storedir isn't -1 we
     * can't store it
     */
    if ((objsize == -1) && (max_objsize != -1))
        return false;

    /*
     * Else, make sure that the max object size is larger than objsize
     */
    return max_objsize > objsize;
}