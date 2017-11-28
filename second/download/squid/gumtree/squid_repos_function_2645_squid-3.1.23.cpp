bool
DescriptorSet::add(int fd)
{
    assert(0 <= fd && fd < capacity_); // \todo: replace with Must()

    if (has(fd))
        return false; // already have it

    assert(size_ < capacity_); // \todo: replace with Must()
    const int pos = size_++;
    index_[fd] = pos;
    descriptors_[pos] = fd;
    return true; // really added
}