void Ipc::Coordinator::registerStrand(const StrandCoord& strand)
{
    debugs(54, 3, HERE << "registering kid" << strand.kidId <<
           ' ' << strand.tag);
    if (StrandCoord* found = findStrand(strand.kidId)) {
        const String oldTag = found->tag;
        *found = strand;
        if (oldTag.size() && !strand.tag.size())
            found->tag = oldTag; // keep more detailed info (XXX?)
    } else {
        strands_.push_back(strand);
    }

    // notify searchers waiting for this new strand, if any
    typedef Searchers::iterator SRI;
    for (SRI i = searchers.begin(); i != searchers.end();) {
        if (i->tag == strand.tag) {
            notifySearcher(*i, strand);
            i = searchers.erase(i);
        } else {
            ++i;
        }
    }
}