unsigned char
ClassCBucket::findHostMapPosition (unsigned char const host) const
{
    return individuals.findKeyIndex(host);
}