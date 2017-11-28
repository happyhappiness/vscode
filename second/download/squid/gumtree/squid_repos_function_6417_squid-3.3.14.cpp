Mgr::FunAction::Pointer
Mgr::FunAction::Create(const Command::Pointer &aCmd, OBJH* aHandler)
{
    return new FunAction(aCmd, aHandler);
}