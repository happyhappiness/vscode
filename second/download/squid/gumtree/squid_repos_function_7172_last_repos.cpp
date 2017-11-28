String Ipc::Port::MakeAddr(const char* processLabel, int id)
{
    assert(id >= 0);
    String addr = channelPathPfx;
    addr.append(service_name.c_str());
    addr.append(processLabel);
    addr.append('-');
    addr.append(xitoa(id));
    addr.append(".ipc");
    return addr;
}