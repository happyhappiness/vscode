Ipc::StrandCoord* Ipc::Coordinator::findStrand(int kidId)
{
    typedef StrandCoords::iterator SI;
    for (SI iter = strands_.begin(); iter != strands_.end(); ++iter) {
        if (iter->kidId == kidId)
            return &(*iter);
    }
    return NULL;
}