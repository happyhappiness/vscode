void
Adaptation::Ecap::XactionRep::resume()
{
    // go async to gain exception protection and done()-based job destruction
    typedef NullaryMemFunT<Adaptation::Ecap::XactionRep> Dialer;
    AsyncCall::Pointer call = asyncCall(93, 5, "Adaptation::Ecap::XactionRep::doResume",
                                        Dialer(this, &Adaptation::Ecap::XactionRep::doResume));
    ScheduleCallHere(call);
}