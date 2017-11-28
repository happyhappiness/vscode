void
Rock::Rebuild::mapSlot(const SlotId slotId, const DbCellHeader &header)
{
    LoadingSlot slot = loadingSlot(slotId);
    assert(!slot.mapped());
    assert(!slot.freed());
    slot.mapped(true);

    Ipc::StoreMapSlice slice;
    slice.next = header.nextSlot;
    slice.size = header.payloadSize;
    sd->map->importSlice(slotId, slice);
}