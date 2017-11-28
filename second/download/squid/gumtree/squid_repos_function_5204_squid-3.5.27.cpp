bool
Rock::Rebuild::canAdd(const sfileno fileno, const SlotId slotId, const DbCellHeader &header) const
{
    if (!sameEntry(fileno, header)) {
        debugs(79, 7, "cannot add; wrong entry");
        return false;
    }

    const LoadingEntry &le = entries[slotId];
    // We cannot add a slot that was already declared free or mapped.
    if (le.freed || le.mapped) {
        debugs(79, 7, "cannot add; freed/mapped: " << le.freed << le.mapped);
        return false;
    }

    if (slotId == header.firstSlot) {
        // If we are the inode, the anchored flag cannot be set yet.
        if (entries[fileno].anchored) {
            debugs(79, 7, "cannot add; extra anchor");
            return false;
        }

        // And there should have been some other slot for this entry to exist.
        if (le.more < 0) {
            debugs(79, 7, "cannot add; missing slots");
            return false;
        }

        return true;
    }

    // We are the continuation slice so the more field is reserved for us.
    if (le.more >= 0) {
        debugs(79, 7, "cannot add; foreign slot");
        return false;
    }

    return true;
}