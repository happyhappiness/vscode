void
ShmWriter::copyToShmSlice(Ipc::StoreMap::Slice &slice)
{
    Ipc::Mem::PageId page = store.pageForSlice(lastSlice);
    debugs(20, 7, "entry " << *entry << " slice " << lastSlice << " has " <<
           page);

    Must(bufWritten <= bufSize);
    const int64_t writingDebt = bufSize - bufWritten;
    const int64_t pageSize = Ipc::Mem::PageSize();
    const int64_t sliceOffset = totalWritten % pageSize;
    const int64_t copySize = std::min(writingDebt, pageSize - sliceOffset);
    memcpy(static_cast<char*>(PagePointer(page)) + sliceOffset, buf + bufWritten,
           copySize);

    debugs(20, 7, "copied " << slice.size << '+' << copySize << " bytes of " <<
           entry << " from " << sliceOffset << " in " << page);

    slice.size += copySize;
    bufWritten += copySize;
    totalWritten += copySize;
    // fresh anchor.basics.swap_file_sz is already set [to the stale value]

    // either we wrote everything or we filled the entire slice
    Must(bufWritten == bufSize || sliceOffset + copySize == pageSize);
}