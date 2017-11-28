void
UFSStoreState::ioCompletedNotification()
{
    if (opening) {
        opening = false;
        debugs(79, 3, "UFSStoreState::ioCompletedNotification: dirno " <<
               swap_dirn  << ", fileno "<< std::setfill('0') << std::hex <<
               std::setw(8) << swap_filen  << " status "<< std::setfill(' ') <<
               std::dec << theFile->error());

        assert (FILE_MODE(mode) == O_RDONLY);
        openDone();

        return;
    }

    if (creating) {
        creating = false;
        debugs(79, 3, "UFSStoreState::ioCompletedNotification: dirno " <<
               swap_dirn  << ", fileno "<< std::setfill('0') << std::hex <<
               std::setw(8) << swap_filen  << " status "<< std::setfill(' ') <<
               std::dec << theFile->error());

        openDone();

        return;
    }

    assert (!(closing ||opening));
    debugs(79, 3, "diskd::ioCompleted: dirno " << swap_dirn  << ", fileno "<<
           std::setfill('0') << std::hex << std::setw(8) << swap_filen  <<
           " status "<< std::setfill(' ') << std::dec << theFile->error());

    /* Ok, notification past open means an error has occured */
    assert (theFile->error());
    tryClosing();
}