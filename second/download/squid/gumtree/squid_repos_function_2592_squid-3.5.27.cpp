MemBlobStats&
MemBlobStats::operator += (const MemBlobStats& s)
{
    alloc+=s.alloc;
    live+=s.live;
    append+=s.append;
    liveBytes+=s.liveBytes;

    return *this;
}