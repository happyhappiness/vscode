void Adaptation::Icap::Launcher::swanSong()
{
    if (theInitiator.set())
        tellQueryAborted(true); // always final here because abnormal

    if (theXaction.set())
        clearAdaptation(theXaction);

    Adaptation::Initiate::swanSong();
}