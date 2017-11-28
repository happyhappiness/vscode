std::ostream *
Adaptation::Ecap::Host::openDebug(libecap::LogVerbosity lv)
{
    const int squidLevel = SquidLogLevel(lv);
    const int squidSection = 93; // XXX: this should be a global constant
    // XXX: Debug.h should provide this to us
    if ((Debug::level = squidLevel) <= Debug::Levels[squidSection])
        return &Debug::getDebugOut();
    else
        return NULL;
}