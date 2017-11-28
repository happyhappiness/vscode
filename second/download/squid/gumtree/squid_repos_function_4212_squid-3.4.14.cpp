void Adaptation::Icap::ServiceRep::startGettingOptions()
{
    Must(!theOptionsFetcher);
    debugs(93,6, HERE << "will get new options " << status());

    // XXX: "this" here is "self"; works until refcounting API changes
    theOptionsFetcher = initiateAdaptation(
                            new Adaptation::Icap::OptXactLauncher(this));
    // TODO: timeout in case Adaptation::Icap::OptXact never calls us back?
    // Such a timeout should probably be a generic AsyncStart feature.
}