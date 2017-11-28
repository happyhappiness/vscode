static void
statStoreEntry(MemBuf * mb, StoreEntry * e)
{
    MemObject *mem = e->mem_obj;
    mb->Printf("KEY %s\n", e->getMD5Text());
    mb->Printf("\t%s\n", describeStatuses(e));
    mb->Printf("\t%s\n", storeEntryFlags(e));
    mb->Printf("\t%s\n", e->describeTimestamps());
    mb->Printf("\t%d locks, %d clients, %d refs\n",
               (int) e->locks(),
               storePendingNClients(e),
               (int) e->refcount);
    mb->Printf("\tSwap Dir %d, File %#08X\n",
               e->swap_dirn, e->swap_filen);

    if (mem != NULL)
        mem->stat (mb);

    mb->Printf("\n");
}