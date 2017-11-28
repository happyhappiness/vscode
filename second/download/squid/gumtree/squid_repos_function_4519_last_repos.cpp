SwapDir &
Store::Disks::dir(const int i) const
{
    SwapDir *sd = INDEXSD(i);
    assert(sd);
    return *sd;
}