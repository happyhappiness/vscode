bool
ACLChecklist::matchChild(const Acl::InnerNode *current, Acl::Nodes::const_iterator pos, const ACL *child)
{
    assert(current && child);

    // Remember the current tree location to prevent "async loop" cases where
    // the same child node wants to go async more than once.
    matchLoc_ = Breadcrumb(current, pos);
    asyncLoopDepth_ = 0;

    // if there are any breadcrumbs left, then follow them on the way down
    bool result = false;
    if (matchPath.empty()) {
        result = child->matches(this);
    } else {
        const Breadcrumb top(matchPath.top());
        assert(child == top.parent);
        matchPath.pop();
        result = top.parent->resumeMatchingAt(this, top.position);
    }

    if (asyncInProgress()) {
        // We get here for node N that called goAsync() and then, as the call
        // stack unwinds, for the nodes higher in the ACL tree that led to N.
        matchPath.push(Breadcrumb(current, pos));
    } else {
        asyncLoc_.clear();
    }

    matchLoc_.clear();
    return result;
}