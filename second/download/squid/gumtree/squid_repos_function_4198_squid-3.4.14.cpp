bool Adaptation::Icap::ServiceRep::allows206() const
{
    Must(hasOptions());
    if (theOptions->allow206)
        return true; // in the future, we may have ACLs to prevent 206s
    return false;
}