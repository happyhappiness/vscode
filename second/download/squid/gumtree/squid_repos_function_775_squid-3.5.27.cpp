void
ClientHttpRequest::startAdaptation(const Adaptation::ServiceGroupPointer &g)
{
    debugs(85, 3, HERE << "adaptation needed for " << this);
    assert(!virginHeadSource);
    assert(!adaptedBodySource);
    virginHeadSource = initiateAdaptation(
                           new Adaptation::Iterator(request, NULL, al, g));

    // we could try to guess whether we can bypass this adaptation
    // initiation failure, but it should not really happen
    Must(initiated(virginHeadSource));
}