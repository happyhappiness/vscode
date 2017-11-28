void
UFSStoreState::openDone()
{
    if (closing)
        debugs(0,0,HERE << "already closing in openDone()!?");

    if (theFile->error()) {
        tryClosing();
        return;
    }

    if (FILE_MODE(mode) == O_WRONLY) {
        drainWriteQueue();

    } else if ((FILE_MODE(mode) == O_RDONLY) && !closing) {
        if (kickReadQueue())
            return;
    }

    if (flags.try_closing)
        tryClosing();

    debugs(79, 3, "UFSStoreState::openDone: exiting");
}