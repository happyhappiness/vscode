void Adaptation::Icap::Launcher::start()
{
    Adaptation::Initiate::start();

    Must(theInitiator.set());
    launchXaction("first");
}