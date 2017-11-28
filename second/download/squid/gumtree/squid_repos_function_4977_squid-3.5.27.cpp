void
Acl::InnerNode::add(ACL *node)
{
    assert(node != NULL);
    nodes.push_back(node);
    aclRegister(node);
}