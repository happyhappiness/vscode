static int ping_arrived_iter(void *udata, void *val)
{
    h2_proxy_stream *stream = val;
    if (stream->waiting_on_ping) {
        stream->waiting_on_ping = 0;
        stream_resume(stream);
    }
    return 1;
}