void
Adaptation::AccessCheck::callBack(const ServiceGroupPointer &g)
{
    debugs(93,3, HERE << g);
    CallJobHere1(93, 5, theInitiator, Adaptation::Initiator,
                 noteAdaptationAclCheckDone, g);
    mustStop("done"); // called back or will never be able to call back
}