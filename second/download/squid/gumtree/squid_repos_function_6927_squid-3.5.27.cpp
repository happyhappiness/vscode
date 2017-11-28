AsyncCall::Pointer
Ipc::Inquirer::DequeueRequest(unsigned int requestId)
{
    debugs(54, 3, HERE << " requestId " << requestId);
    Must(requestId != 0);
    AsyncCall::Pointer call;
    RequestsMap::iterator request = TheRequestsMap.find(requestId);
    if (request != TheRequestsMap.end()) {
        call = request->second;
        Must(call != NULL);
        TheRequestsMap.erase(request);
    }
    return call;
}