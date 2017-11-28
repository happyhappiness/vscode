int
ConnStateData::getAvailableBufferLength() const
{
    assert (in.allocatedSize > in.notYetUsed); // allocated more than used
    const size_t result = in.allocatedSize - in.notYetUsed - 1;
    // huge request_header_max_size may lead to more than INT_MAX unused space
    assert (static_cast<ssize_t>(result) <= INT_MAX);
    return result;
}