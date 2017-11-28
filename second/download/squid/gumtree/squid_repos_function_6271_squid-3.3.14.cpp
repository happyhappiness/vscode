int Kid::termSignal() const
{
    return WTERMSIG(status);
}