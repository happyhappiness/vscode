void
Rock::IoState::finishedWriting(const int errFlag)
{
    // we incremented offset_ while accumulating data in write()
    callBack(errFlag);
}