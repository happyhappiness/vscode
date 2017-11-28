void Adaptation::Icap::ServiceRep::callException(const std::exception &e)
{
    clearAdaptation(theOptionsFetcher);
    debugs(93,2, "ICAP probably failed to fetch options (" << e.what() <<
           ")" << status());
    handleNewOptions(0);
}