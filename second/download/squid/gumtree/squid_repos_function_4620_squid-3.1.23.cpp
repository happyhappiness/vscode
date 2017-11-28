void
CossSwapDir::parse(int anIndex, char *aPath)
{
    unsigned int i;
    unsigned int size;
    off_t max_offset;

    i = GetInteger();
    size = i << 10;		/* Mbytes to Kbytes */

    if (size <= 0)
        fatal("storeCossDirParse: invalid size value");

    index = anIndex;

    path = xstrdup(aPath);

    max_size = size;

    parseOptions(0);

    if (NULL == io)
        changeIO(DiskIOModule::FindDefault());

    /* Enforce maxobjsize being set to something */
    if (max_objsize == -1)
        fatal("COSS requires max-size to be set to something other than -1!\n");

    if (max_objsize > COSS_MEMBUF_SZ)
        fatalf("COSS max-size option must be less than COSS_MEMBUF_SZ (%d)\n",
               COSS_MEMBUF_SZ);

    /*
     * check that we won't overflow sfileno later.  0xFFFFFF is the
     * largest possible sfileno, assuming sfileno is a 25-bit
     * signed integer, as defined in structs.h.
     */
    max_offset = (off_t) 0xFFFFFF << blksz_bits;

    if ((off_t)max_size > (max_offset>>10)) {
        debugs(47, 0, "COSS block-size = " << (1<<blksz_bits) << " bytes");
        debugs(47,0, "COSS largest file offset = " << (max_offset >> 10) << " KB");
        debugs(47, 0, "COSS cache_dir size = " << max_size << " KB");
        fatal("COSS cache_dir size exceeds largest offset\n");
    }
}