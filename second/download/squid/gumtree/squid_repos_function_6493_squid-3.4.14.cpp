size_t
Ipc::Mem::PageLimit(const int purpose)
{
    Must(0 <= purpose && purpose <= PageId::maxPurpose);
    return TheLimits[purpose];
}