void
Adaptation::ServiceGroup::finalizeMsg(const char *msg, const String &culprit,
                                      bool error) const
{
    const int level = error ? DBG_CRITICAL :DBG_IMPORTANT;
    const char *pfx = error ? "ERROR: " : "WARNING: ";
    debugs(93,level, pfx << msg << ' ' << culprit << " in " << kind << " '" <<
           id << "'");
}