void
Fs::Ufs::UFSStoreState::write(char const *buf, size_t size, off_t aOffset, FREE * free_func)
{
    debugs(79, 3, "UFSStoreState::write: dirn " << swap_dirn  << ", fileno "<<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) << swap_filen);

    if (theFile->error()) {
        debugs(79, DBG_IMPORTANT,HERE << "avoid write on theFile with error");
        debugs(79, DBG_IMPORTANT,HERE << "calling free_func for " << (void*) buf);
        free_func((void*)buf);
        return;
    }

    queueWrite(buf, size, aOffset, free_func);
    drainWriteQueue();
}