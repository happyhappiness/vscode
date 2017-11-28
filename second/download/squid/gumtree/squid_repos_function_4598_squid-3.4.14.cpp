allow_t
Acl::Tree::lastAction() const
{
    if (actions.empty())
        return ACCESS_DUNNO;
    return actions.back();
}