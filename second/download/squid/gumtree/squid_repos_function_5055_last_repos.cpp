void
Rock::HeaderUpdater::NoteDoneReading(void *data, int errflag, StoreIOState::Pointer)
{
    // TODO: Avoid Rock::StoreIOStateCb for jobs to protect jobs for "free".
    CallJobHere1(47, 7,
                 CbcPointer<HeaderUpdater>(static_cast<HeaderUpdater*>(data)),
                 Rock::HeaderUpdater,
                 noteDoneReading,
                 errflag);
}