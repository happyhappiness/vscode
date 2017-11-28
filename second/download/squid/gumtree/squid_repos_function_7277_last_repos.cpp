std::ostream &
operator <<(std::ostream &os, const Mgr::Command &cmd)
{
    if (cmd.profile != NULL)
        return os << *cmd.profile;
    return os << "undef";
}