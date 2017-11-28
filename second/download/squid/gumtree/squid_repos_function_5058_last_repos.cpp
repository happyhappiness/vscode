void
Rock::HeaderUpdater::NoteDoneWriting(void *data, int errflag, StoreIOState::Pointer)
{
    CallJobHere1(47, 7,
                 CbcPointer<HeaderUpdater>(static_cast<HeaderUpdater*>(data)),
                 Rock::HeaderUpdater,
                 noteDoneWriting,
                 errflag);
}