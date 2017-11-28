void
IndependentRunner::unregisterRunner()
{
    if (Runners *runners = FindRunners())
        runners->erase(this);
    // else it is too late, finishShutdown() has been called
}