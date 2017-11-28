void Adaptation::Iterator::start()
{
    Adaptation::Initiate::start();

    thePlan = ServicePlan(theGroup, filter());

    // Add adaptation group name once and now, before
    // dynamic groups change it at step() time.
    if (Adaptation::Config::needHistory && !thePlan.exhausted() && (dynamic_cast<ServiceSet *>(theGroup.getRaw()) || dynamic_cast<ServiceChain *>(theGroup.getRaw()))) {
        HttpRequest *request = dynamic_cast<HttpRequest*>(theMsg);
        if (!request)
            request = theCause;
        Must(request);
        Adaptation::History::Pointer ah = request->adaptHistory(true);
        auto gid = StringToSBuf(theGroup->id);
        ah->recordAdaptationService(gid);
    }

    step();
}