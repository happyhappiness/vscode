void
Adaptation::Ecap::XactionRep::moveAbContent()
{
    Must(proxyingAb == opOn);
    const libecap::Area c = theMaster->abContent(0, libecap::nsize);
    debugs(93,5, HERE << "up to " << c.size << " bytes");
    if (c.size == 0 && abProductionFinished) { // no ab now and in the future
        stopProducingFor(answer().body_pipe, abProductionAtEnd);
        proxyingAb = opComplete;
        debugs(93,5, HERE << "last adapted body data retrieved");
    } else if (c.size > 0) {
        if (const size_t used = answer().body_pipe->putMoreData(c.start, c.size))
            theMaster->abContentShift(used);
    }
}