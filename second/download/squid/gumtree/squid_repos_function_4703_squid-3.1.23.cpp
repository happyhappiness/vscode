void
UFSStoreState::closeCompleted()
{
    assert (closing);
    debugs(79, 3, "UFSStoreState::closeCompleted: dirno " << swap_dirn  <<
           ", fileno "<< std::setfill('0') << std::hex << std::setw(8) <<
           swap_filen  << " status "<< std::setfill(' ') << std::dec <<
           theFile->error());

    if (theFile->error()) {
        debugs(79,3,HERE<< "theFile->error() ret " << theFile->error());
        doCloseCallback(DISK_ERROR);
    } else {
        doCloseCallback(DISK_OK);
    }

    closing = false;
}