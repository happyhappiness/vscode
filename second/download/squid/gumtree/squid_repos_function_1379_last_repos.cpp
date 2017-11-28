void
helperSubmit(helper * hlp, const char *buf, HLPCB * callback, void *data)
{
    if (!hlp || !hlp->trySubmit(buf, callback, data))
        SubmissionFailure(hlp, callback, data);
}