StoreIOState::Pointer
Fs::Ufs::UFSStrategy::open(SwapDir * SD, StoreEntry * e, StoreIOState::STFNCB *,
                           StoreIOState::STIOCB * aCallback, void *callback_data)
{
    assert (((UFSSwapDir *)SD)->IO == this);
    debugs(79, 3, HERE << "fileno "<< std::setfill('0') << std::hex
           << std::uppercase << std::setw(8) << e->swap_filen);

    /* to consider: make createstate a private UFSStrategy call */
    StoreIOState::Pointer sio = createState (SD, e, aCallback, callback_data);

    sio->mode |= O_RDONLY;

    Fs::Ufs::UFSStoreState *state = dynamic_cast <Fs::Ufs::UFSStoreState *>(sio.getRaw());

    assert (state);

    char *path = ((UFSSwapDir *)SD)->fullPath(e->swap_filen, NULL);

    DiskFile::Pointer myFile = newFile (path);

    if (myFile.getRaw() == NULL)
        return NULL;

    state->theFile = myFile;

    state->opening = true;

    myFile->open (sio->mode, 0644, state);

    if (myFile->error())
        return NULL;

    return sio;
}