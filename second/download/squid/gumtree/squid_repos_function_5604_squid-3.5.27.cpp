void
Comm::CallbackTableDestruct()
{
    // release any Comm::Connections being held.
    for (int pos = 0; pos < Squid_MaxFD; ++pos) {
        iocb_table[pos].readcb.conn = NULL;
        iocb_table[pos].writecb.conn = NULL;
    }
    safe_free(iocb_table);
}