void Ipc::Port::noteRead(const CommIoCbParams& params)
{
    debugs(54, 6, HERE << params.conn << " flag " << params.flag <<
           " [" << this << ']');
    if (params.flag == COMM_OK) {
        assert(params.buf == buf.raw());
        receive(buf);
    }
    // TODO: if there was a fatal error on our socket, close the socket before
    // trying to listen again and print a level-1 error message.

    doListen();
}