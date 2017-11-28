void
ACLHasComponentData::parseComponent(const char *token)
{
    if (RequestStr.cmp(token) == 0)
        componentMethods[coRequest] = &ACLChecklist::hasRequest;
    else if (ResponseStr.cmp(token) == 0)
        componentMethods[coResponse] = &ACLChecklist::hasReply;
    else if (AleStr.cmp(token) == 0)
        componentMethods[coAle] = &ACLChecklist::hasAle;
    else {
        debugs(28, DBG_CRITICAL, "FATAL: unsupported component '" << token << "' for 'has' acl");
        self_destruct();
    }
}