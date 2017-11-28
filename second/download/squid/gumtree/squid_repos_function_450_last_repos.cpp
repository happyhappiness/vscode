void
ClientHttpRequest::handleAdaptationBlock(const Adaptation::Answer &answer)
{
    request->detailError(ERR_ACCESS_DENIED, ERR_DETAIL_REQMOD_BLOCK);
    AclMatchedName = answer.ruleId.termedBuf();
    assert(calloutContext);
    calloutContext->clientAccessCheckDone(ACCESS_DENIED);
    AclMatchedName = NULL;
}