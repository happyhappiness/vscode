void Adaptation::Icap::ServiceRep::handleNewOptions(Adaptation::Icap::Options *newOptions)
{
    // new options may be NULL
    changeOptions(newOptions);

    debugs(93,3, HERE << "got new options and is now " << status());

    scheduleUpdate(optionsFetchTime());
    scheduleNotification();
}