void
CossState::lockMemBuf()
{
    CossMemBuf *t = SD->storeCossFilenoToMembuf(swap_filen);
    debugs(79, 3, "CossState::lockMemBuf: locking " << t << ", lockcount " << t->lockcount);
    locked_membuf = t;
    ++t->lockcount;
}