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