bool
statefulhelper::trySubmit(const char *buf, HLPCB * callback, void *data, helper_stateful_server *lastserver)
{
    if (!prepSubmit())
        return false; // request was dropped

    submit(buf, callback, data, lastserver); // will send or queue
    return true; // request submitted or queued
}