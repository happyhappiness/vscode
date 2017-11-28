bool
RegisterRunner(RegisteredRunner *rr)
{
    Must(!dynamic_cast<IndependentRunner*>(rr));

    if (FindRunners()) {
        RegisterRunner_(rr);
        return true;
    }

    // past finishShutdown
    GetRidOfRunner(rr);
    return false;
}