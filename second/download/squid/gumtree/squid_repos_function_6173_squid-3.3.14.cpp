bool
Ipc::OpenListenerParams::operator <(const OpenListenerParams &p) const
{
    if (sock_type != p.sock_type)
        return sock_type < p.sock_type;

    if (proto != p.proto)
        return proto < p.proto;

    // ignore flags and fdNote differences because they do not affect binding

    return addr.compareWhole(p.addr) < 0;
}