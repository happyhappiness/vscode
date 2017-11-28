bool Ipc::UdsSender::doneAll() const
{
    return !writing && !sleeping && UdsOp::doneAll();
}