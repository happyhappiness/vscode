std::ostream *
Adaptation::Ecap::Host::openDebug(libecap::LogVerbosity lv)
{
    const int squidLevel = SquidLogLevel(lv);
    const int squidSection = 93; // XXX: this should be a global constant
    return Debug::Enabled(squidSection, squidLevel) ?
           &Debug::Start(squidSection, squidLevel) :
           nullptr;
}