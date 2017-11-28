void
Comm::CallbackTableInit()
{
    // XXX: convert this to a std::map<> ?
    iocb_table = static_cast<CbEntry*>(xcalloc(Squid_MaxFD, sizeof(CbEntry)));
    for (int pos = 0; pos < Squid_MaxFD; ++pos) {
        iocb_table[pos].fd = pos;
        iocb_table[pos].readcb.type = IOCB_READ;
        iocb_table[pos].writecb.type = IOCB_WRITE;
    }
}