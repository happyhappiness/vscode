void
Adaptation::Ecap::Host::closeDebug(std::ostream *debug)
{
    if (debug)
        Debug::Finish();
}