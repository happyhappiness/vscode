bool
Rock::SwapDir::addEntry(const int filen, const DbCellHeader &header, const StoreEntry &from)
{
    debugs(47, 8, HERE << &from << ' ' << from.getMD5Text() <<
           ", filen="<< std::setfill('0') << std::hex << std::uppercase <<
           std::setw(8) << filen);

    sfileno newLocation = 0;
    if (Ipc::StoreMapSlot *slot = map->openForWriting(reinterpret_cast<const cache_key *>(from.key), newLocation)) {
        if (filen == newLocation) {
            slot->set(from);
            map->extras(filen) = header;
        } // else some other, newer entry got into our cell
        map->closeForWriting(newLocation, false);
        return filen == newLocation;
    }

    return false;
}