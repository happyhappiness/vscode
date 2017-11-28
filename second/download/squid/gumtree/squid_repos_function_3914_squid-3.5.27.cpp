void
Adaptation::AccessCheck::noteAnswer(allow_t answer)
{
    Must(!candidates.empty()); // the candidate we were checking must be there
    debugs(93,5, HERE << topCandidate() << " answer=" << answer);

    if (answer == ACCESS_ALLOWED) { // the rule matched
        ServiceGroupPointer g = topGroup();
        if (g != NULL) { // the corresponding group found
            callBack(g);
            Must(done());
            return;
        }
    }

    // no match or the group disappeared during reconfiguration
    candidates.erase(candidates.begin());
    checkCandidates();
}