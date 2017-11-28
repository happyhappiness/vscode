ssize_t
mem_hdr::copy(StoreIOBuffer const &target) const
{

    assert(target.range().end > target.range().start);
    debugs(19, 6, "memCopy: " << this << " " << target.range());

    /* we shouldn't ever ask for absent offsets */

    if (nodes.size() == 0) {
        debugs(19, DBG_IMPORTANT, "mem_hdr::copy: No data to read");
        debugDump();
        assert (0);
        return 0;
    }

    /* RC: the next assert is nearly useless */
    assert(target.length > 0);

    /* Seek our way into store */
    mem_node *p = getBlockContainingLocation(target.offset);

    if (!p) {
        debugs(19, DBG_IMPORTANT, "memCopy: could not find start of " << target.range() <<
               " in memory.");
        debugDump();
        fatal("Squid has attempted to read data from memory that is not present. This is an indication of of (pre-3.0) code that hasn't been updated to deal with sparse objects in memory. Squid should coredump.allowing to review the cause. Immediately preceding this message is a dump of the available data in the format [start,end). The [ means from the value, the ) means up to the value. I.e. [1,5) means that there are 4 bytes of data, at offsets 1,2,3,4.\n");
        return 0;
    }

    size_t bytes_to_go = target.length;
    char *ptr_to_buf = target.data;
    int64_t location = target.offset;

    /* Start copying begining with this block until
     * we're satiated */

    while (p && bytes_to_go > 0) {
        size_t bytes_to_copy = copyAvailable (p,
                                              location, bytes_to_go, ptr_to_buf);

        /* hit a sparse patch */

        if (bytes_to_copy == 0)
            return target.length - bytes_to_go;

        location += bytes_to_copy;

        ptr_to_buf += bytes_to_copy;

        bytes_to_go -= bytes_to_copy;

        p = getBlockContainingLocation(location);
    }

    return target.length - bytes_to_go;
}