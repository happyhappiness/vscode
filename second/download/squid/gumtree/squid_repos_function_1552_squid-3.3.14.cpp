bool
ClassCBucket::individualAllocated (unsigned char host) const
{
    return individualUsed(findHostMapPosition (host));
}