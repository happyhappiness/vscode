static void
SslBumpEstablish(const Comm::ConnectionPointer &, char *, size_t, Comm::Flag errflag, int, void *data)
{
    ClientHttpRequest *r = static_cast<ClientHttpRequest*>(data);
    debugs(85, 5, HERE << "responded to CONNECT: " << r << " ? " << errflag);

    assert(r && cbdataReferenceValid(r));
    r->sslBumpEstablish(errflag);
}