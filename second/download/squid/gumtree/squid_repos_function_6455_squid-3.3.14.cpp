Mgr::IntervalAction::Pointer
Mgr::IntervalAction::Create5min(const CommandPointer &cmd)
{
    return new IntervalAction(cmd, 5, 0);
}