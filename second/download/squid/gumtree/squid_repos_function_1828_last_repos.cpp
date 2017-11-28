time_t
FwdState::ForwardTimeout(const time_t fwdStart)
{
    // time already spent on forwarding (0 if clock went backwards)
    const time_t timeSpent = diffOrZero(squid_curtime, fwdStart);
    return diffOrZero(Config.Timeout.forward, timeSpent);
}