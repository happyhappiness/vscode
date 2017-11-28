bool BodyPipe::expectMoreAfter(uint64_t offset) const
{
    assert(theGetSize <= offset);
    return offset < thePutSize || // buffer has more now or
           (!productionEnded() && mayNeedMoreData()); // buffer will have more
}