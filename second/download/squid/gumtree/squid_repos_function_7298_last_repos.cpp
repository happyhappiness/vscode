Mgr::IntervalAction::Pointer
Mgr::IntervalAction::Create60min(const CommandPointer &cmd)
{
    return new IntervalAction(cmd, 60, 0);
}