int
DelayTaggedCmp(DelayTaggedBucket::Pointer const &left, DelayTaggedBucket::Pointer const &right)
{
    /* for rate limiting, case insensitive */
    return left->tag.caseCmp(right->tag);
}