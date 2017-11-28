libecap::Message &
Adaptation::Ecap::XactionRep::adapted()
{
    Must(theAnswerRep);
    return *theAnswerRep;
}