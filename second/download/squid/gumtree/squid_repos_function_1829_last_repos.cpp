bool
FwdState::EnoughTimeToReForward(const time_t fwdStart)
{
    return ForwardTimeout(fwdStart) > 0;
}