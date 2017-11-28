void Adaptation::Icap::Launcher::noteAdaptationAnswer(HttpMsg *message)
{
    sendAnswer(message);
    clearAdaptation(theXaction);
    Must(done());
    debugs(93,3, HERE << "Adaptation::Icap::Launcher::noteAdaptationAnswer exiting ");
}