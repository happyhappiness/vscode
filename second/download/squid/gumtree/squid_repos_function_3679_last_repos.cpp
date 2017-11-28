void Adaptation::Icap::ServiceRep::scheduleNotification()
{
    debugs(93,7, HERE << "will notify " << theClients.size() << " clients");
    CallJobHere(93, 5, this, Adaptation::Icap::ServiceRep, noteTimeToNotify);
}