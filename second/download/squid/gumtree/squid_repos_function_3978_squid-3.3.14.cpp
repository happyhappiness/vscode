libecap::Message &
Adaptation::Ecap::XactionRep::adapted()
{
    Must(theAnswerRep != NULL);
    return *theAnswerRep;
}