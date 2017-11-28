Ipc::Response::Pointer
Mgr::Response::clone() const
{
    return new Response(*this);
}