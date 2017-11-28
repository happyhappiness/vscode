Adaptation::Service &
Adaptation::Ecap::XactionRep::service()
{
    Must(theService != NULL);
    return *theService;
}