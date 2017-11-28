size_t Adaptation::Icap::Preview::debt() const
{
    Must(enabled());
    return done() ? 0 : (theAd - theWritten);
}