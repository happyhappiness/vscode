void
ServerStateData::startAdaptation(const Adaptation::ServiceGroupPointer &group, HttpRequest *cause)
{
    debugs(11, 5, "ServerStateData::startAdaptation() called");
    // check whether we should be sending a body as well
    // start body pipe to feed ICAP transaction if needed
    assert(!virginBodyDestination);
    HttpReply *vrep = virginReply();
    assert(!vrep->body_pipe);
    int64_t size = 0;
    if (vrep->expectingBody(cause->method, size) && size) {
        virginBodyDestination = new BodyPipe(this);
        vrep->body_pipe = virginBodyDestination;
        debugs(93, 6, HERE << "will send virgin reply body to " <<
               virginBodyDestination << "; size: " << size);
        if (size > 0)
            virginBodyDestination->setBodySize(size);
    }

    adaptedHeadSource = initiateAdaptation(
                            new Adaptation::Iterator(vrep, cause, group));
    startedAdaptation = initiated(adaptedHeadSource);
    Must(startedAdaptation);
}