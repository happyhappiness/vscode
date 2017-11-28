allow_t
Acl::Tree::winningAction() const
{
    return actionAt(lastMatch_ - nodes.begin());
}