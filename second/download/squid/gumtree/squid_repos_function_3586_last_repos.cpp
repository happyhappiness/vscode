bool Adaptation::Icap::Preview::done() const
{
    Must(enabled());
    return theState >= stIeof;
}