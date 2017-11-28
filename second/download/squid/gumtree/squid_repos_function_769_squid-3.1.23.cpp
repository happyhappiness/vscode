void
ClientHttpRequest::noteAdaptationQueryAbort(bool final)
{
    clearAdaptation(virginHeadSource);
    assert(!adaptedBodySource);
    handleAdaptationFailure(!final);
}