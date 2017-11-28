SBufStats&
SBufStats::operator +=(const SBufStats& ss)
{
    alloc += ss.alloc;
    allocCopy += ss.allocCopy;
    allocFromCString += ss.allocFromCString;
    assignFast += ss.assignFast;
    clear += ss.clear;
    append += ss.append;
    moves += ss.moves;
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
    caseChange += ss.caseChange;
    cowFast += ss.cowFast;
    cowSlow += ss.cowSlow;
    live += ss.live;

    return *this;
}