void Adaptation::Iterator::swanSong()
{
    if (theInitiator.set())
        tellQueryAborted(true); // abnormal condition that should not happen

    if (initiated(theLauncher))
        clearAdaptation(theLauncher);

    Adaptation::Initiate::swanSong();
}