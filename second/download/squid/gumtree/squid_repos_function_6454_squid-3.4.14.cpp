void Ipc::Strand::handleCacheMgrResponse(const Mgr::Response& response)
{
    Mgr::Forwarder::HandleRemoteAck(response.requestId);
}