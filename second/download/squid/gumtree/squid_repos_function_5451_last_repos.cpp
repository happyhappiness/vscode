void
MemPoolChunked::push(void *obj)
{
    void **Free;
    /* XXX We should figure out a sane way of avoiding having to clear
     * all buffers. For example data buffers such as used by MemBuf do
     * not really need to be cleared.. There was a condition based on
     * the object size here, but such condition is not safe.
     */
    if (doZero)
        memset(obj, 0, obj_size);
    Free = (void **)obj;
    *Free = freeCache;
    freeCache = obj;
    (void) VALGRIND_MAKE_MEM_NOACCESS(obj, obj_size);
}