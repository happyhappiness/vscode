mem_node *
mem_hdr::getBlockContainingLocation (int64_t location) const
{
    // Optimize: do not create a whole mem_node just to store location
    mem_node target (location);
    target.nodeBuffer.length = 1;
    mem_node *const *result = nodes.find (&target, NodeCompare);

    if (result)
        return *result;

    return NULL;
}