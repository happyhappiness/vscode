std::ostream &Ipc::StartListeningCb::startPrint(std::ostream &os) const
{
    return os << "(" << conn << ", err=" << errNo;
}