bool
Rock::IoState::write(char const *buf, size_t size, off_t coreOff, FREE *dtor)
{
    bool success = false;
    try {
        tryWrite(buf, size, coreOff);
        success = true;
    } catch (const std::exception &ex) { // TODO: should we catch ... as well?
        debugs(79, 2, "db write error: " << ex.what());
        dir->writeError(*this);
        finishedWriting(DISK_ERROR);
        // 'this' might be gone beyond this point; fall through to free buf
    }

    // careful: 'this' might be gone here

    if (dtor)
        (dtor)(const_cast<char*>(buf)); // cast due to a broken API?

    return success;
}