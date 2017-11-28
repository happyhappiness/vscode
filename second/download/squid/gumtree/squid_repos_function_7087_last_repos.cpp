void
Ipc::Inquirer::handleRemoteAck(Response::Pointer response)
{
    debugs(54, 4, HERE << status());
    request->requestId = 0;
    removeTimeoutEvent();
    if (aggregate(response)) {
        Must(!done()); // or we should not be called
        ++pos; // advance after a successful inquiry
        inquire();
    } else {
        mustStop("error");
    }
}