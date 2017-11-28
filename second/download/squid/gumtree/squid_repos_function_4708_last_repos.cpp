std::ostream &
SBufStats::dump(std::ostream& os) const
{
    MemBlobStats ststats = MemBlob::GetStats();
    os <<
       "SBuf stats:\nnumber of allocations: " << alloc <<
       "\ncopy-allocations: " << allocCopy <<
       "\ncopy-allocations from C String: " << allocFromCString <<
       "\nlive references: " << live <<
       "\nno-copy assignments: " << assignFast <<
       "\nclearing operations: " << clear <<
       "\nappend operations: " << append <<
       "\nmove operations: " << moves <<
       "\ndump-to-ostream: " << toStream <<
       "\nset-char: " << setChar <<
       "\nget-char: " << getChar <<
       "\ncomparisons with data-scan: " << compareSlow <<
       "\ncomparisons not requiring data-scan: " << compareFast <<
       "\ncopy-out ops: " << copyOut <<
       "\nraw access to memory: " << rawAccess <<
       "\nNULL terminate C string: " << nulTerminate <<
       "\nchop operations: " << chop <<
       "\ntrim operations: " << trim <<
       "\nfind: " << find <<
       "\ncase-change ops: " << caseChange <<
       "\nCOW not actually requiring a copy: " << cowFast <<
       "\nCOW: " << cowSlow <<
       "\naverage store share factor: " <<
       (ststats.live != 0 ? static_cast<float>(live)/ststats.live : 0) <<
       std::endl;
    return os;
}