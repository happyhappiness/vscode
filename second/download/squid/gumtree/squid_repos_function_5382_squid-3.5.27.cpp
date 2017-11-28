void
Client::adjustBodyBytesRead(const int64_t delta)
{
    int64_t &bodyBytesRead = originalRequest()->hier.bodyBytesRead;

    // if we got here, do not log a dash even if we got nothing from the server
    if (bodyBytesRead < 0)
        bodyBytesRead = 0;

    bodyBytesRead += delta; // supports negative and zero deltas

    // check for overflows ("infinite" response?) and undeflows (a bug)
    Must(bodyBytesRead >= 0);
}