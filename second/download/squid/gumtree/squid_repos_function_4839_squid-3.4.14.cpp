void
CossSwapDir::storeCossMemBufUnlock(StoreIOState::Pointer sio)
{
    CossMemBuf *t = storeCossFilenoToMembuf(sio->swap_filen);
    CossState *cstate = dynamic_cast<CossState *>(sio.getRaw());

    if (NULL == t)
        return;

    debugs(79, 3, "storeCossMemBufUnlock: unlocking " << t << ", lockcount " << t->lockcount);

    -- t->lockcount;

    cstate->locked_membuf = NULL;

    t->maybeWrite(this);
}