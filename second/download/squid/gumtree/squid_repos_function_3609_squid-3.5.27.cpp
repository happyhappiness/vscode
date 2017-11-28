void
ClientSocketContext::noteIoError(const int xerrno)
{
    if (http) {
        if (xerrno == ETIMEDOUT)
            http->al->http.timedout = true;
        else // even if xerrno is zero (which means read abort/eof)
            http->al->http.aborted = true;
    }
}