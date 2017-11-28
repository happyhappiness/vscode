bool Kid::signaled() const
{
    return (pid > 0) && !running() && WIFSIGNALED(status);
}