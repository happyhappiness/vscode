void
storeClose(StoreIOState::Pointer sio, int how)
{
    if (sio->flags.closing) {
        debugs(20,3,HERE << "storeClose: flags.closing already set, bailing");
        return;
    }

    sio->flags.closing = 1;

    debugs(20,3,HERE << "storeClose: calling sio->close(" << how << ")");
    sio->close(how);
}