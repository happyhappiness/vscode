int64_t
MemObject::availableForSwapOut() const
{
    return endOffset() - swapout.queue_offset;
}