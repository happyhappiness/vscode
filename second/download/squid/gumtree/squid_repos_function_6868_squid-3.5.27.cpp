bool Kid::shouldRestart() const
{
    return !(running() ||
             exitedHappy() ||
             hopeless() ||
             shutting_down ||
             signaled(SIGKILL) || // squid -k kill
             signaled(SIGINT) || // unexpected forced shutdown
             signaled(SIGTERM)); // unexpected forced shutdown
}