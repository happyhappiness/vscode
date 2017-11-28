void Adaptation::Icap::ServiceRep::noteAdaptationAnswer(HttpMsg *msg)
{
    Must(initiated(theOptionsFetcher));
    clearAdaptation(theOptionsFetcher);

    Must(msg);

    debugs(93,5, HERE << "is interpreting new options " << status());

    Adaptation::Icap::Options *newOptions = NULL;
    if (HttpReply *r = dynamic_cast<HttpReply*>(msg)) {
        newOptions = new Adaptation::Icap::Options;
        newOptions->configure(r);
    } else {
        debugs(93,1, "ICAP service got wrong options message " << status());
    }

    handleNewOptions(newOptions);
}