bool Kid::calledExit() const
{
    return (pid > 0) && !running() && WIFEXITED(status);
}