void Adaptation::Icap::Launcher::noteAdaptationQueryAbort(bool final)
{
    debugs(93,5, HERE << "launches: " << theLaunches << "; final: " << final);
    clearAdaptation(theXaction);

    Must(done()); // swanSong will notify the initiator
}