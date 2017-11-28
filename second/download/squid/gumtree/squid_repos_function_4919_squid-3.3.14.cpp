void
Fs::Ufs::UFSSwapDir::parseSizeL1L2()
{
    int i = GetInteger();
    if (i <= 0)
        fatal("UFSSwapDir::parseSizeL1L2: invalid size value");

    const uint64_t size = static_cast<uint64_t>(i) << 20; // MBytes to Bytes

    /* just reconfigure it */
    if (reconfiguring) {
        if (size == maxSize())
            debugs(3, 2, "Cache dir '" << path << "' size remains unchanged at " << i << " MB");
        else
            debugs(3, DBG_IMPORTANT, "Cache dir '" << path << "' size changed to " << i << " MB");
    }

    max_size = size;

    l1 = GetInteger();

    if (l1 <= 0)
        fatal("UFSSwapDir::parseSizeL1L2: invalid level 1 directories value");

    l2 = GetInteger();

    if (l2 <= 0)
        fatal("UFSSwapDir::parseSizeL1L2: invalid level 2 directories value");
}