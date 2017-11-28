void
CompositePoolNode::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (CompositePoolNode);
    ::operator delete (address);
}