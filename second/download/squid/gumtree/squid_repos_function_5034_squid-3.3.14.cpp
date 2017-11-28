void
Comm::IoCallback::setCallback(Comm::iocb_type t, AsyncCall::Pointer &cb, char *b, FREE *f, int sz)
{
    assert(!active());
    assert(type == t);
    assert(cb != NULL);

    callback = cb;
    buf = b;
    freefunc = f;
    size = sz;
    offset = 0;
}