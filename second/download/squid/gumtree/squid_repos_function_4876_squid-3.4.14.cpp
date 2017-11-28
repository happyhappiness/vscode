void
CossSwapDir::parse(int anIndex, char *aPath)
{
    const int i = GetInteger();
    if (i <= 0)
        fatal("storeCossDirParse: invalid size value");

    index = anIndex;

    path = xstrdup(aPath);

    max_size = static_cast<uint64_t>(i) << 20; // MBytes to Bytes

    parseOptions(0);

    if (NULL == io)
        changeIO(DiskIOModule::FindDefault());

    /* Enforce maxobjsize being set to something */
    if (max_objsize == -1)
        fatal("COSS requires max-size to be set to something other than -1!\n");

    if (max_objsize > COSS_MEMBUF_SZ)
        fatalf("COSS max-size option must be less than COSS_MEMBUF_SZ (%d)\n",
               COSS_MEMBUF_SZ);

    // check that we won't overflow sfileno later.
    const uint64_t max_offset = (uint64_t)SwapFilenMax << blksz_bits;

    if (maxSize() > max_offset) {
        debugs(47, DBG_CRITICAL, "COSS block-size = " << (1<<blksz_bits) << " bytes");
        debugs(47, DBG_CRITICAL, "COSS largest file offset = " << (max_offset >> 10) << " KB");
        debugs(47, DBG_CRITICAL, "COSS cache_dir size = " << (maxSize() >> 10) << " KB");
        fatal("COSS cache_dir size exceeds largest offset\n");
    }
}