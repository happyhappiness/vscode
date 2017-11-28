StoreIOState::Pointer
Fs::Ufs::UFSStrategy::create(SwapDir * SD, StoreEntry * e, StoreIOState::STFNCB *,
                             StoreIOState::STIOCB * aCallback, void *callback_data)
{
    assert (((UFSSwapDir *)SD)->IO == this);
    /* Allocate a number */
    sfileno filn = ((UFSSwapDir *)SD)->mapBitAllocate();
    debugs(79, 3, HERE << "fileno "<< std::setfill('0') <<
           std::hex << std::uppercase << std::setw(8) << filn);

    /* Shouldn't we handle a 'bitmap full' error here? */

    StoreIOState::Pointer sio = createState (SD, e, aCallback, callback_data);

    sio->mode |= O_WRONLY | O_CREAT | O_TRUNC;

    sio->swap_filen = filn;

    Fs::Ufs::UFSStoreState *state = dynamic_cast <Fs::Ufs::UFSStoreState *>(sio.getRaw());

    assert (state);

    char *path = ((UFSSwapDir *)SD)->fullPath(filn, NULL);

    DiskFile::Pointer myFile = newFile (path);

    if (myFile.getRaw() == NULL) {
        ((UFSSwapDir *)SD)->mapBitReset (filn);
        return NULL;
    }

    state->theFile = myFile;

    state->creating = true;

    myFile->create (state->mode, 0644, state);

    if (myFile->error()) {
        ((UFSSwapDir *)SD)->mapBitReset (filn);
        return NULL;
    }

    /* now insert into the replacement policy */
    ((UFSSwapDir *)SD)->replacementAdd(e);

    return sio;
}