bool
MemStore::copyFromShmSlice(StoreEntry &e, const StoreIOBuffer &buf, bool eof)
{
    debugs(20, 7, "buf: " << buf.offset << " + " << buf.length);

    // from store_client::readBody()
    // parse headers if needed; they might span multiple slices!
    HttpReply *rep = (HttpReply *)e.getReply();
    if (rep->pstate < psParsed) {
        // XXX: have to copy because httpMsgParseStep() requires 0-termination
        MemBuf mb;
        mb.init(buf.length+1, buf.length+1);
        mb.append(buf.data, buf.length);
        mb.terminate();
        const int result = rep->httpMsgParseStep(mb.buf, buf.length, eof);
        if (result > 0) {
            assert(rep->pstate == psParsed);
            EBIT_CLR(e.flags, ENTRY_FWD_HDR_WAIT);
        } else if (result < 0) {
            debugs(20, DBG_IMPORTANT, "Corrupted mem-cached headers: " << e);
            return false;
        } else { // more slices are needed
            assert(!eof);
        }
    }
    debugs(20, 7, "rep pstate: " << rep->pstate);

    // local memory stores both headers and body so copy regardless of pstate
    const int64_t offBefore = e.mem_obj->endOffset();
    assert(e.mem_obj->data_hdr.write(buf)); // from MemObject::write()
    const int64_t offAfter = e.mem_obj->endOffset();
    // expect to write the entire buf because StoreEntry::write() never fails
    assert(offAfter >= 0 && offBefore <= offAfter &&
           static_cast<size_t>(offAfter - offBefore) == buf.length);
    return true;
}