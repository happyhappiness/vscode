void
Rock::HeaderUpdater::noteDoneReading(int errflag)
{
    debugs(47, 5, errflag << " writer=" << writer);
    if (!reader) {
        Must(!errflag); // we only initiate successful closures
        Must(writer); // otherwise we would be done() and would not be called
    } else {
        reader = nullptr; // we are done reading
        Must(errflag); // any external closures ought to be errors
        mustStop("read error");
    }
}