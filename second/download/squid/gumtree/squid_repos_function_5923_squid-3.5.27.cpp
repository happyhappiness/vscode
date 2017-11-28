void
AsyncCall::make()
{
    debugs(debugSection, debugLevel, HERE << "make call " << name <<
           " [" << id << ']');
    if (canFire()) {
        fire();
        return;
    }

    if (!isCanceled) // we did not cancel() when returning false from canFire()
        isCanceled = "unknown reason";

    debugs(debugSection, debugLevel, HERE << "will not call " << name <<
           " [" << id << ']' << " because of " << isCanceled);
}