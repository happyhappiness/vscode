void Adaptation::Icap::ServiceRep::noteAdaptationQueryAbort(bool)
{
    Must(initiated(theOptionsFetcher));
    clearAdaptation(theOptionsFetcher);

    debugs(93,3, HERE << "failed to fetch options " << status());
    handleNewOptions(0);
}