void
Rock::HeaderUpdater::NoteRead(void *data, const char *buf, ssize_t result, StoreIOState::Pointer)
{
    // TODO: Avoid Rock::StoreIOStateCb for jobs to protect jobs for "free".
    CallJobHere1(47, 7,
                 CbcPointer<HeaderUpdater>(static_cast<HeaderUpdater*>(data)),
                 Rock::HeaderUpdater,
                 noteRead,
                 result);
}