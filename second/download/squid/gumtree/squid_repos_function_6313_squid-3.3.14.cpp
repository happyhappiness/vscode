void
Ipc::Inquirer::requestTimedOut()
{
    debugs(54, 3, HERE);
    if (request->requestId != 0) {
        DequeueRequest(request->requestId);
        request->requestId = 0;
        Must(!done()); // or we should not be called
        ++pos; // advance after a failed inquiry
        inquire();
    }
}