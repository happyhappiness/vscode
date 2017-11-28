bool Adaptation::Icap::Preview::ieof() const
{
    Must(enabled());
    return theState == stIeof;
}