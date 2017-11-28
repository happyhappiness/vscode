bool
EventDialer::canDial(AsyncCall &call)
{
    // TODO: add Parent::canDial() that always returns true
    //if (!Parent::canDial())
    //    return false;

    if (isLockedArg && !cbdataReferenceValid(theArg))
        return call.cancel("stale handler data");

    return true;
}