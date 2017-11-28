bool Adaptation::Icap::Launcher::doneAll() const
{
    return (!theInitiator || !theXaction) && Adaptation::Initiate::doneAll();
}