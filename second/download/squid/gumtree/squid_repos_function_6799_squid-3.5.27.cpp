void
Ipc::Coordinator::handleSearchRequest(const Ipc::StrandSearchRequest &request)
{
    // do we know of a strand with the given search tag?
    const StrandCoord *strand = NULL;
    typedef StrandCoords::const_iterator SCCI;
    for (SCCI i = strands_.begin(); !strand && i != strands_.end(); ++i) {
        if (i->tag == request.tag)
            strand = &(*i);
    }

    if (strand) {
        notifySearcher(request, *strand);
        return;
    }

    searchers.push_back(request);
    debugs(54, 3, HERE << "cannot yet tell kid" << request.requestorId <<
           " who " << request.tag << " is");
}