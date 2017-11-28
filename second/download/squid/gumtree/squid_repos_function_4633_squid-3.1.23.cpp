void
UFSSwapDir::parseSizeL1L2()
{
    int i = GetInteger();
    if (i <= 0)
        fatal("UFSSwapDir::parseSizeL1L2: invalid size value");

    size_t size = i << 10;		/* Mbytes to kbytes */

    /* just reconfigure it */
    if (reconfiguring) {
        if (size == max_size)
            debugs(3, 2, "Cache dir '" << path << "' size remains unchanged at " << size << " KB");
        else
            debugs(3, 1, "Cache dir '" << path << "' size changed to " << size << " KB");
    }

    max_size = size;

    l1 = GetInteger();

    if (l1 <= 0)
        fatal("UFSSwapDir::parseSizeL1L2: invalid level 1 directories value");

    l2 = GetInteger();

    if (l2 <= 0)
        fatal("UFSSwapDir::parseSizeL1L2: invalid level 2 directories value");
}