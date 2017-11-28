void
ACLChecklist::matchAclList(const ACLList * head, bool const fast)
{
    PROF_start(aclMatchAclList);
    const ACLList *node = head;

    finished_ = false;

    while (node) {
        bool nodeMatched = node->matches(this);

        if (fast)
            changeState(NullState::Instance());

        if (finished()) {
            PROF_stop(aclMatchAclList);
            return;
        }

        if (!nodeMatched || state_ != NullState::Instance()) {
            debugs(28, 3, "aclmatchAclList: " << this << " returning false (AND list entry failed to match)");

            bool async = state_ != NullState::Instance();

            checkForAsync();

            bool async_in_progress = asyncInProgress();
            debugs(28, 3, "aclmatchAclList: async=" << (async ? 1 : 0) <<
                   " nodeMatched=" << (nodeMatched ? 1 : 0) <<
                   " async_in_progress=" << (async_in_progress ? 1 : 0) <<
                   " lastACLResult() = " << (lastACLResult() ? 1 : 0) <<
                   " finished() = " << finished());

            if (finished()) {
                PROF_stop(aclMatchAclList);
                return;
            }

            if (async && nodeMatched && !asyncInProgress() && lastACLResult()) {
                // async acl, but using cached response, and it was a match
                node = node->next;
                continue;
            }

            PROF_stop(aclMatchAclList);

            return;
        }

        node = node->next;
    }

    debugs(28, 3, "aclmatchAclList: " << this << " returning true (AND list satisfied)");

    markFinished();
    PROF_stop(aclMatchAclList);
}