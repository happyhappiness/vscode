String Ipc::Port::MakeAddr(const char* pathAddr, int id)
{
    assert(id >= 0);
    String addr = pathAddr;
    addr.append('-');
    addr.append(xitoa(id));
    addr.append(".ipc");
    return addr;
}