bool
Fs::Ufs::UFSStoreState::write(char const *buf, size_t size, off_t aOffset, FREE * free_func)
{
    debugs(79, 3, "UFSStoreState::write: dirn " << swap_dirn  << ", fileno "<<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) << swap_filen);

    if (theFile->error()) {
        debugs(79, DBG_IMPORTANT,HERE << "avoid write on theFile with error");
        debugs(79, DBG_IMPORTANT,HERE << "calling free_func for " << (void*) buf);
        free_func((void*)buf);
        return false;
    }

    const Store::Disk &dir = *INDEXSD(swap_dirn);
    if (static_cast<uint64_t>(offset_ + size) > static_cast<uint64_t>(dir.maxObjectSize())) {
        debugs(79, 2, "accepted unknown-size entry grew too big: " <<
               (offset_ + size) << " > " << dir.maxObjectSize());
        free_func((void*)buf);
        tryClosing();
        return false;
    }

    debugs(79, 3, (void*)this << " queueing write of size " << size);
    pending_writes.emplace(buf, size, aOffset, free_func);
    drainWriteQueue();
    return true;
}