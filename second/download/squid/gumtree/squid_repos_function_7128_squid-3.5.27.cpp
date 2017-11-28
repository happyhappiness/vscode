Ipc::Request::Pointer
Mgr::Request::clone() const
{
    return new Request(*this);
}