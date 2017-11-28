void
Adaptation::Ecap::XactionRep::noteAbContentAvailable()
{
    Must(proxyingAb == opOn && !abProductionFinished);
    moveAbContent();
}