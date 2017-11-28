void
Adaptation::AccessCheck::AccessCheckCallbackWrapper(int answer, void *data)
{
    debugs(93, 8, HERE << "callback answer=" << answer);
    AccessCheck *ac = (AccessCheck*)data;

    /** \todo AYJ 2008-06-12: If answer == ACCESS_REQ_PROXY_AUTH
     * we should be kicking off an authentication before continuing
     * with this request. see bug 2400 for details.
     */

    // convert to async call to get async call protections and features
    typedef UnaryMemFunT<AccessCheck, int> MyDialer;
    AsyncCall::Pointer call =
        asyncCall(93,7, "Adaptation::AccessCheck::noteAnswer",
                  MyDialer(ac, &Adaptation::AccessCheck::noteAnswer,
                           answer==ACCESS_ALLOWED));
    ScheduleCallHere(call);

}