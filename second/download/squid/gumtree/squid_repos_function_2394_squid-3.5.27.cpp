void
MemObject::dump() const
{
    data_hdr.dump();
#if 0
    /* do we want this one? */
    debugs(20, DBG_IMPORTANT, "MemObject->data.origin_offset: " << (data_hdr.head ? data_hdr.head->nodeBuffer.offset : 0));
#endif

    debugs(20, DBG_IMPORTANT, "MemObject->start_ping: " << start_ping.tv_sec  << "."<< std::setfill('0') << std::setw(6) << start_ping.tv_usec);
    debugs(20, DBG_IMPORTANT, "MemObject->inmem_hi: " << data_hdr.endOffset());
    debugs(20, DBG_IMPORTANT, "MemObject->inmem_lo: " << inmem_lo);
    debugs(20, DBG_IMPORTANT, "MemObject->nclients: " << nclients);
    debugs(20, DBG_IMPORTANT, "MemObject->reply: " << _reply);
    debugs(20, DBG_IMPORTANT, "MemObject->request: " << request);
    debugs(20, DBG_IMPORTANT, "MemObject->logUri: " << logUri_);
    debugs(20, DBG_IMPORTANT, "MemObject->storeId: " << storeId_);
}