void
UFSStoreState::close()
{
    debugs(79, 3, "UFSStoreState::close: dirno " << swap_dirn  << ", fileno "<<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) << swap_filen);
    tryClosing();
}