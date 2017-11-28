const libecap::Message &
Adaptation::Ecap::XactionRep::cause()
{
    Must(theCauseRep != NULL);
    return *theCauseRep;
}