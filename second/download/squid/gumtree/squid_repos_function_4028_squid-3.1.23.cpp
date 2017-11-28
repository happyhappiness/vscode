void Adaptation::Icap::ServiceRep::changeOptions(Adaptation::Icap::Options *newOptions)
{
    debugs(93,8, HERE << "changes options from " << theOptions << " to " <<
           newOptions << ' ' << status());

    delete theOptions;
    theOptions = newOptions;
    theSessionFailures = 0;
    isSuspended = 0;
    theLastUpdate = squid_curtime;

    checkOptions();
    announceStatusChange("down after an options fetch failure", true);
}