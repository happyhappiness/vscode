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


void
CossSwapDir::reconfigure(int index, char *path)
{
    unsigned int i;
    unsigned int size;

    i = GetInteger();
    size = i << 10;		/* Mbytes to Kbytes */

    if (size <= 0)
        fatal("storeCossDirParse: invalid size value");

    if (size == (size_t)max_size)
        debugs(3, 1, "Cache COSS dir '" << path << "' size remains unchanged at " << size << " KB");
    else {
        debugs(3, 1, "Cache COSS dir '" << path << "' size changed to " << size << " KB");
        max_size = size;
    }

    /* Enforce maxobjsize being set to something */
    if (max_objsize == -1)
        fatal("COSS requires max-size to be set to something other than -1!\n");
}

void
CossSwapDir::dump(StoreEntry &entry)const
{
    storeAppendPrintf(&entry, " %" PRIu64, (max_size >> 10));
    dumpOptions(&entry);
}

CossSwapDir::CossSwapDir() : SwapDir ("coss"), swaplog_fd(-1), count(0), current_membuf (NULL), current_offset(0), numcollisions(0),  blksz_bits(0), io (NULL), ioModule(NULL), currentIOOptions(new ConfigOptionVector()), stripe_path(NULL)
{
    membufs.head = NULL;
    membufs.tail = NULL;
    cossindex.head = NULL;
    cossindex.tail = NULL;
    blksz_mask = (1 << blksz_bits) - 1;
