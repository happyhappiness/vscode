void Adaptation::Icap::ModXact::disableBypass(const char *reason, bool includingGroupBypass)
{
    if (canStartBypass) {
        debugs(93,7, HERE << "will never start bypass because " << reason);
        canStartBypass = false;
    }
    if (protectGroupBypass && includingGroupBypass) {
        debugs(93,7, HERE << "not protecting group bypass because " << reason);
        protectGroupBypass = false;
    }
}