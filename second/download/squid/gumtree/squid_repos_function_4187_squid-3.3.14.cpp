void Adaptation::Icap::ServiceRep::announceStatusChange(const char *downPhrase, bool important) const
{
    if (wasAnnouncedUp == up()) // no significant changes to announce
        return;

    const char *what = cfg().bypass ? "optional" : "essential";
    const char *state = wasAnnouncedUp ? downPhrase : "up";
    const int level = important ? 1 :2;
    debugs(93,level, what << " ICAP service is " << state << ": " <<
           cfg().uri << ' ' << status());

    wasAnnouncedUp = !wasAnnouncedUp;
}