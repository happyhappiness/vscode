void
helper::submit(const char *buf, HLPCB * callback, void *data)
{
    Helper::Xaction *r = new Helper::Xaction(callback, data, buf);
    submitRequest(r);
    debugs(84, DBG_DATA, Raw("buf", buf, strlen(buf)));
}