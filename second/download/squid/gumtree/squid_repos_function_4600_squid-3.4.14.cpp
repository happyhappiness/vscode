void
Acl::Tree::add(ACL *rule, const allow_t &action)
{
    // either all rules have actions or none
    assert(nodes.size() == actions.size());
    InnerNode::add(rule);
    actions.push_back(action);
}