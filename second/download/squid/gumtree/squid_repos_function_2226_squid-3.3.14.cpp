void
ServerStateData::addVirginReplyBody(const char *data, ssize_t len)
{
    adjustBodyBytesRead(len);

#if USE_ADAPTATION
    assert(!adaptationAccessCheckPending); // or would need to buffer while waiting
    if (startedAdaptation) {
        adaptVirginReplyBody(data, len);
        return;
    }
#endif
    storeReplyBody(data, len);
}