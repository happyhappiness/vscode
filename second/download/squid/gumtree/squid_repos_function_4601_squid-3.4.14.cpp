void
Acl::Tree::add(ACL *rule)
{
    // either all rules have actions or none
    assert(actions.empty());
    InnerNode::add(rule);
}