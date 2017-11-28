Comm::ConnectionPointer &
Ipc::UdsOp::conn()
{
    if (!Comm::IsConnOpen(conn_)) {
        if (options & COMM_DOBIND)
            unlink(address.sun_path);
        if (conn_ == NULL)
            conn_ = new Comm::Connection;
        conn_->fd = comm_open_uds(SOCK_DGRAM, 0, &address, options);
        Must(Comm::IsConnOpen(conn_));
    }
    return conn_;
}