void Ipc::UdsOp::clearTimeout()
{
    commUnsetConnTimeout(conn());
}