static inline void
GetRidOfRunner(RegisteredRunner *rr)
{
    if (!dynamic_cast<IndependentRunner*>(rr))
        delete rr;
    // else ignore; IndependentRunner
}