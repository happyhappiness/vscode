int
DescriptorSet::pop()
{
    assert(!empty());
    const int lastPos =--size_;
    const int lastFd = descriptors_[lastPos];
    assert(0 <= lastFd && lastFd < capacity_);

    // cleanup
    descriptors_[lastPos] = -1;
    index_[lastFd] = -1;

    return lastFd;
}