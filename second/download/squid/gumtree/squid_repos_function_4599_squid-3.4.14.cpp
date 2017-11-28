allow_t
Acl::Tree::actionAt(const Nodes::size_type pos) const
{
    assert(pos < nodes.size());
    if (actions.size()) {
        assert(actions.size() == nodes.size());
        return actions[pos];
    }
    // default for matched rules in trees without actions
    return ACCESS_ALLOWED;
}