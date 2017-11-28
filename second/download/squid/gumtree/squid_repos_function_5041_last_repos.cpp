void
Rock::IoState::finishedWriting(const int errFlag)
{
    // we incremented offset_ while accumulating data in write()
    // we do not reset writeableAnchor_ here because we still keep the lock
    if (touchingStoreEntry())
        CollapsedForwarding::Broadcast(*e);
    callBack(errFlag);
}