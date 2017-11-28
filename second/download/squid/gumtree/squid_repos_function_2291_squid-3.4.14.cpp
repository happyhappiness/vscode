void
ServerStateData::noteAdaptationAclCheckDone(Adaptation::ServiceGroupPointer group)
{
    adaptationAccessCheckPending = false;

    if (abortOnBadEntry("entry went bad while waiting for ICAP ACL check"))
        return;

    // TODO: Should nonICAP and postICAP path check this on the server-side?
    // That check now only happens on client-side, in processReplyAccess().
    if (virginReply()->expectedBodyTooLarge(*request)) {
        sendBodyIsTooLargeError();
        return;
    }
    // TODO: Should we check receivedBodyTooLarge on the server-side as well?

    if (!group) {
        debugs(11,3, HERE << "no adapation needed");
        setFinalReply(virginReply());
        processReplyBody();
        return;
    }

    startAdaptation(group, originalRequest());
    processReplyBody();
}