static void
commLingerTimeout(const FdeCbParams &params)
{
    debugs(5, 3, "commLingerTimeout: FD " << params.fd);
    comm_close(params.fd);
}