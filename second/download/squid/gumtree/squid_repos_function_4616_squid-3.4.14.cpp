void
ACLChecklist::matchAndFinish()
{
    bool result = false;
    if (matchPath.empty()) {
        result = accessList->matches(this);
    } else {
        const Breadcrumb top(matchPath.top());
        matchPath.pop();
        result = top.parent->resumeMatchingAt(this, top.position);
    }

    if (result) // the entire tree matched
        markFinished(accessList->winningAction(), "match");
}