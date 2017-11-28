int
Acl::InnerNode::match(ACLChecklist *checklist)
{
    return doMatch(checklist, nodes.begin());
}