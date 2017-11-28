StoreIOState::Pointer
Rock::SwapDir::createUpdateIO(const Ipc::StoreMapUpdate &update, StoreIOState::STFNCB *cbFile, StoreIOState::STIOCB *cbIo, void *data)
{
    if (!theFile || theFile->error()) {
        debugs(47,4, theFile);
        return nullptr;
    }

    Must(update.fresh);
    Must(update.fresh.fileNo >= 0);

    Rock::SwapDir::Pointer self(this);
    IoState *sio = new IoState(self, update.entry, cbFile, cbIo, data);

    sio->swap_dirn = index;
    sio->swap_filen = update.fresh.fileNo;
    sio->writeableAnchor_ = update.fresh.anchor;

    debugs(47,5, "dir " << index << " updating filen " <<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) <<
           sio->swap_filen << std::dec << " starting at " <<
           diskOffset(sio->swap_filen));

    sio->file(theFile);
    return sio;
}