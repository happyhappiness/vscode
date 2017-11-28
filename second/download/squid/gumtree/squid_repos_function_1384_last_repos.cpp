bool
helper::trySubmit(const char *buf, HLPCB * callback, void *data)
{
    if (!prepSubmit())
        return false; // request was dropped

    submit(buf, callback, data); // will send or queue
    return true; // request submitted or queued
}