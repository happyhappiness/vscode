bool
SwapDir::active() const
{
    if (IamWorkerProcess())
        return true;

    // we are inside a disker dedicated to this disk
    if (KidIdentifier == disker)
        return true;

    return false; // Coordinator, wrong disker, etc.
}