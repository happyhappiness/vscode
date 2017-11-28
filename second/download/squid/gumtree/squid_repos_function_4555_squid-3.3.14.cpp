ACLChecklist::NodeMatchingResult
ACLChecklist::matchNode(const ACLList &node, bool const fast)
{
    const bool nodeMatched = node.matches(this);
    const bool needsAsync = asyncNeeded();
    const bool matchFinished = finished();

    debugs(28, 3, HERE << this <<
           " matched=" << nodeMatched <<
           " async=" << needsAsync <<
           " finished=" << matchFinished);

    /* There are eight possible outcomes of the matches() call based on
       (matched, async, finished) permutations. We support these four:
       matched,!async,!finished: a match (must check next rule node)
       !matched,!async,!finished: a mismatch (whole rule fails to match)
       !matched,!async,finished: error or special condition (propagate)
       !matched,async,!finished: ACL needs to make an async call (pause)
     */

    if (nodeMatched) {
        // matches() should return false in all special cases
        assert(!needsAsync && !matchFinished);
        return nmrMatch;
    }

    if (matchFinished) {
        // we cannot be done and need an async call at the same time
        assert(!needsAsync);
        debugs(28, 3, HERE << this << " exception: " << currentAnswer());
        return nmrFinished;
    }

    if (!needsAsync) {
        debugs(28, 3, HERE << this << " simple mismatch");
        return nmrMismatch;
    }

    /* we need an async call */

    if (fast) {
        changeState(NullState::Instance()); // disable async checks
        markFinished(ACCESS_DUNNO, "async required but prohibited");
        debugs(28, 3, HERE << this << " DUNNO because cannot async");
        return nmrFinished;
    }

    debugs(28, 3, HERE << this << " going async");
    return nmrNeedsAsync;
}