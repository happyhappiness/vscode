int
Acl::NotNode::doMatch(ACLChecklist *checklist, Nodes::const_iterator start) const
{
    assert(start == nodes.begin()); // we only have one node

    if (checklist->matchChild(this, start, *start))
        return 0; // converting match into mismatch

    if (!checklist->keepMatching())
        return -1; // suspend on async calls and stop on failures

    return 1; // converting mismatch into match
}