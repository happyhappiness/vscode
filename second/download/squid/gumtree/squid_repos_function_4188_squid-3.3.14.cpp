void Adaptation::Icap::ServiceRep::noteAdaptationAnswer(const Answer &answer)
{
    Must(initiated(theOptionsFetcher));
    clearAdaptation(theOptionsFetcher);

    if (answer.kind == Answer::akError) {
        debugs(93,3, HERE << "failed to fetch options " << status());
        handleNewOptions(0);
        return;
    }

    Must(answer.kind == Answer::akForward); // no akBlock for OPTIONS requests
    HttpMsg *msg = answer.message;
    Must(msg);

    debugs(93,5, HERE << "is interpreting new options " << status());

    Adaptation::Icap::Options *newOptions = NULL;
    if (HttpReply *r = dynamic_cast<HttpReply*>(msg)) {
        newOptions = new Adaptation::Icap::Options;
        newOptions->configure(r);
    } else {
        debugs(93, DBG_IMPORTANT, "ICAP service got wrong options message " << status());
    }

    handleNewOptions(newOptions);
}