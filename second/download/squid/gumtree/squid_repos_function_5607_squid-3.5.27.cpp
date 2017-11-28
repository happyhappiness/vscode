void
Comm::IoCallback::cancel(const char *reason)
{
    if (!active())
        return;

    callback->cancel(reason);
    callback = NULL;
    reset();
}