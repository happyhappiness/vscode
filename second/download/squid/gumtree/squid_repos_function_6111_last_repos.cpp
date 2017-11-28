void
IndependentRunner::registerRunner()
{
    if (FindRunners())
        RegisterRunner_(this);
    // else do nothing past finishShutdown
}