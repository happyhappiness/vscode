bool
DescriptorSet::del(int fd)
{
    assert(0 <= fd && fd < capacity_); // \todo: here and below, use Must()

    if (!has(fd))
        return false; // we do not have it

    assert(!empty());
    const int delPos = index_[fd];
    assert(0 <= delPos && delPos < capacity_);

    // move the last descriptor to the deleted fd position
    // to avoid skipping deleted descriptors in pop()
    const int lastPos = size_-1;
    const int lastFd = descriptors_[lastPos];
    assert(delPos <= lastPos); // may be the same
    descriptors_[delPos] = lastFd;
    index_[lastFd] = delPos;

    descriptors_[lastPos] = -1;
    index_[fd] = -1;
    --size_;

    return true; // really added
}