void
Ssl::Bio::prepReadBuf()
{
    if (rbuf.isNull())
        rbuf.init(4096, 65536);
}