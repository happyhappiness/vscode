void
Mgr::Action::respond(const Request &request)
{
    debugs(16, 5, HERE);

    // Assume most kid classes are fully aggregatable (i.e., they do not dump
    // local info at all). Do not import the remote HTTP fd into our Comm
    // space; collect and send an IPC msg with collected info to Coordinator.
    ::close(request.conn->fd);
    request.conn->fd = -1;
    collect();
    sendResponse(request.requestId);
}