int
Acl::OrNode::doMatch(ACLChecklist *checklist, Nodes::const_iterator start) const
{
    lastMatch_ = nodes.end();

    // find the first node that matches, but stop if things go wrong
    for (Nodes::const_iterator i = start; i != nodes.end(); ++i) {
        if (checklist->matchChild(this, i, *i)) {
            lastMatch_ = i;
            return 1;
        }

        if (!checklist->keepMatching())
            return -1; // suspend on async calls and stop on failures
    }

    // zero and not one on empty because in math empty sum equals zero
    return 0; // all nodes mismatched
}