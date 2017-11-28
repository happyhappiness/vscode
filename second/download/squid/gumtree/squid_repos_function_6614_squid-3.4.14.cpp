Mgr::IndexAction::Pointer
Mgr::IndexAction::Create(const Command::Pointer &cmd)
{
    return new IndexAction(cmd);
}