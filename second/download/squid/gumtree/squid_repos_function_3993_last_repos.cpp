int
Acl::AllOf::doMatch(ACLChecklist *checklist, Nodes::const_iterator start) const
{
    assert(start == nodes.begin()); // we only have one node

    // avoid dereferencing invalid start
    if (empty())
        return 1; // not 0 because in math empty product equals identity

    if (checklist->matchChild(this, start, *start))
        return 1; // match

    return checklist->keepMatching() ? 0 : -1;
}