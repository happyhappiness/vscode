void
CossSwapDir::writeCompleted(int errflag, size_t len, RefCount<WriteRequest> writeRequest)
{
    CossWrite* cossWrite= dynamic_cast<CossWrite *>(writeRequest.getRaw());
    assert (cossWrite);

    debugs(79, 3, "storeCossWriteMemBufDone: buf " << cossWrite->membuf << ", len " << len);

    if (errflag) {
        ++ StoreFScoss::GetInstance().stats.stripe_write.fail;
        debugs(79, DBG_IMPORTANT, "storeCossWriteMemBufDone: got failure (" << errflag << ")");
        debugs(79, DBG_IMPORTANT, "size=" << cossWrite->membuf->diskend - cossWrite->membuf->diskstart);
    } else {
        ++ StoreFScoss::GetInstance().stats.stripe_write.success;
    }

    dlinkDelete(&cossWrite->membuf->node, &membufs);
    cbdataFree(cossWrite->membuf);
    -- StoreFScoss::GetInstance().stats.stripes;
}