int
Acl::AndNode::doMatch(ACLChecklist *checklist, Nodes::const_iterator start) const
{
    // find the first node that does not match
    for (Nodes::const_iterator i = start; i != nodes.end(); ++i) {
        if (!checklist->matchChild(this, i, *i))
            return checklist->keepMatching() ? 0 : -1;
    }

    // one and not zero on empty because in math empty product equals identity
    return 1; // no mismatches found (i.e., all kids matched)
}