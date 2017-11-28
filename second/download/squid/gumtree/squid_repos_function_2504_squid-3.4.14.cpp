std::ostream&
MemBlobStats::dump(std::ostream &os) const
{
    os <<
    "MemBlob created: " << alloc <<
    "\nMemBlob alive: " << live <<
    "\nMemBlob append calls: " << append <<
    "\nMemBlob currently allocated size: " << liveBytes <<
    "\nlive MemBlob mean current allocation size: " <<
    (static_cast<double>(liveBytes)/(live?live:1)) << std::endl;
    return os;
}