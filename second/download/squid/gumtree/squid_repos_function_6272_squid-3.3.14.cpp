bool Kid::signaled(int sgnl) const
{
    return signaled() && (termSignal() == sgnl);
}