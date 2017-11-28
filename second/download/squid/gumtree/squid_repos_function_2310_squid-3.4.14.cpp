void
MemObject::stat(MemBuf * mb) const
{
    mb->Printf("\t%s %s\n",
               RequestMethodStr(method), log_url);
    if (vary_headers)
        mb->Printf("\tvary_headers: %s\n", vary_headers);
    mb->Printf("\tinmem_lo: %" PRId64 "\n", inmem_lo);
    mb->Printf("\tinmem_hi: %" PRId64 "\n", data_hdr.endOffset());
    mb->Printf("\tswapout: %" PRId64 " bytes queued\n",
               swapout.queue_offset);

    if (swapout.sio.getRaw())
        mb->Printf("\tswapout: %" PRId64 " bytes written\n",
                   (int64_t) swapout.sio->offset());

    StoreClientStats statsVisitor(mb);

    for_each<StoreClientStats>(clients, statsVisitor);
}