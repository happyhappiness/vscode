bool
Acl::Tree::bannedAction(ACLChecklist *checklist, Nodes::const_iterator node) const
{
    if (actions.size()) {
        assert(actions.size() == nodes.size());
        const Nodes::size_type pos = node - nodes.begin();
        return checklist->bannedAction(actions.at(pos));
    }
    return false;
}