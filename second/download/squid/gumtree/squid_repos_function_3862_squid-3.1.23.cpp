void
Adaptation::Ecap::XactionRep::noteAbContentDone(bool atEnd)
{
    Must(proxyingAb == opOn && !abProductionFinished);
    abProductionFinished = true;
    abProductionAtEnd = atEnd; // store until ready to stop producing ourselves
    debugs(93,5, HERE << "adapted body production ended");
    moveAbContent();
}