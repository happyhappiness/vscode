void Adaptation::Initiate::swanSong()
{
    debugs(93, 5, HERE << "swan sings" << status());

    if (theInitiator.set()) {
        debugs(93, 3, HERE << "fatal failure; sending abort notification");
        tellQueryAborted(true); // final by default
    }

    debugs(93, 5, HERE << "swan sang" << status());
}