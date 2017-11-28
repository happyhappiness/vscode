SBufStats&
SBufStats::operator +=(const SBufStats& ss)
{
    alloc += ss.alloc;
    allocCopy += ss.allocCopy;
    allocFromString += ss.allocFromString;
    allocFromCString += ss.allocFromCString;
    assignFast += ss.assignFast;
    clear += ss.clear;
    append += ss.append;
    toStream += ss.toStream;
    setChar += ss.setChar;
    getChar += ss.getChar;
    compareSlow += ss.compareSlow;
    compareFast += ss.compareFast;
    copyOut += ss.copyOut;
    rawAccess += ss.rawAccess;
    nulTerminate += ss.nulTerminate;
    chop += ss.chop;
    trim += ss.trim;
    find += ss.find;
    scanf += ss.scanf;
    caseChange += ss.caseChange;
    cowFast += ss.cowFast;
    cowSlow += ss.cowSlow;
    live += ss.live;

    return *this;
}