void *
CompositePoolNode::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (CompositePoolNode);
    return ::operator new (size);
}