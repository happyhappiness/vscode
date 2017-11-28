void
Ipc::Coordinator::handleCacheMgrResponse(const Mgr::Response& response)
{
    Mgr::Inquirer::HandleRemoteAck(response);
}