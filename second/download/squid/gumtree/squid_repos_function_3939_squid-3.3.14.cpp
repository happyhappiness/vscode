bool
Adaptation::Ecap::ServiceRep::handleFinalizeFailure(const char *error)
{
    const bool salvage = cfg().bypass;
    const int level = salvage ? DBG_IMPORTANT :DBG_CRITICAL;
    const char *kind = salvage ? "optional" : "essential";
    debugs(93, level, "ERROR: failed to start " << kind << " eCAP service: " <<
           cfg().uri << ":\n" << error);

    if (!salvage)
        return false; // we cannot handle the problem; the caller may escalate

    // make up() false, preventing new adaptation requests and enabling bypass
    theService.reset();
    debugs(93, level, "WARNING: " << kind << " eCAP service is " <<
           "down after initialization failure: " << cfg().uri);

    return true; // tell the caller to ignore the problem because we handled it
}