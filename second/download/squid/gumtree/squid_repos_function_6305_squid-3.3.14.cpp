void
Ipc::Inquirer::swanSong()
{
    debugs(54, 5, HERE);
    removeTimeoutEvent();
    if (request->requestId > 0) {
        DequeueRequest(request->requestId);
        request->requestId = 0;
    }
    sendResponse();
    cleanup();
}