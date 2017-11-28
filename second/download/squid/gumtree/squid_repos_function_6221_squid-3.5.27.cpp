size_t
DiskdIOStrategy::newInstance()
{
    return ++nextInstanceID;
}