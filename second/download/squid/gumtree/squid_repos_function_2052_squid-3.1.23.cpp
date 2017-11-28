bool
mem_hdr::hasContigousContentRange(Range<int64_t> const & range) const
{
    int64_t currentStart = range.start;

    while (mem_node *curr = getBlockContainingLocation(currentStart)) {
        currentStart = curr->end();

        if (currentStart >= range.end)
            return true;
    }

    return false;
}