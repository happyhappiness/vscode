void
helperStatefulSubmit(statefulhelper * hlp, const char *buf, HLPCB * callback, void *data, helper_stateful_server * lastserver)
{
    if (!hlp || !hlp->trySubmit(buf, callback, data, lastserver))
        SubmissionFailure(hlp, callback, data);
}