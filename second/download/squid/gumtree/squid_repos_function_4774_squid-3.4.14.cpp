bool
Acl::InnerNode::resumeMatchingAt(ACLChecklist *checklist, Nodes::const_iterator pos) const
{
    debugs(28, 5, "checking " << name << " at " << (pos-nodes.begin()));
    const int result = doMatch(checklist, pos);
    const char *extra = checklist->asyncInProgress() ? " async" : "";
    debugs(28, 3, "checked: " << name << " = " << result << extra);

    // merges async and failures (-1) into "not matched"
    return result == 1;
}