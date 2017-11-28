void
MemObject::stat(MemBuf * mb) const
{
    mb->appendf("\t" SQUIDSBUFPH " %s\n", SQUIDSBUFPRINT(method.image()), logUri());
    if (!vary_headers.isEmpty())
        mb->appendf("\tvary_headers: " SQUIDSBUFPH "\n", SQUIDSBUFPRINT(vary_headers));
    mb->appendf("\tinmem_lo: %" PRId64 "\n", inmem_lo);
    mb->appendf("\tinmem_hi: %" PRId64 "\n", data_hdr.endOffset());
    mb->appendf("\tswapout: %" PRId64 " bytes queued\n", swapout.queue_offset);

    if (swapout.sio.getRaw())
        mb->appendf("\tswapout: %" PRId64 " bytes written\n", (int64_t) swapout.sio->offset());

    if (xitTable.index >= 0)
        mb->appendf("\ttransient index: %d state: %d\n", xitTable.index, xitTable.io);
    if (memCache.index >= 0)
        mb->appendf("\tmem-cache index: %d state: %d offset: %" PRId64 "\n", memCache.index, memCache.io, memCache.offset);
    if (object_sz >= 0)
        mb->appendf("\tobject_sz: %" PRId64 "\n", object_sz);
    if (smpCollapsed)
        mb->appendf("\tsmp-collapsed\n");

    StoreClientStats statsVisitor(mb);

    for_each<StoreClientStats>(clients, statsVisitor);
}