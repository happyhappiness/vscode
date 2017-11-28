static void
SubmissionFailure(helper *hlp, HLPCB *callback, void *data)
{
    auto result = Helper::Error;
    if (!hlp) {
        debugs(84, 3, "no helper");
        result = Helper::Unknown;
    }
    // else pretend the helper has responded with ERR

    callback(data, Helper::Reply(result));
}