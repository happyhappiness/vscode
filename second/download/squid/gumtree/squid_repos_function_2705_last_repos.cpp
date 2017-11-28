void
ShmWriter::copyToShm()
{
    Must(bufSize > 0); // do not use up shared memory pages for nothing
    Must(firstSlice < 0 || lastSlice >= 0);

    // fill, skip slices that are already full
    while (bufWritten < bufSize) {
        Ipc::StoreMap::Slice &slice = store.nextAppendableSlice(fileNo, lastSlice);
        if (firstSlice < 0)
            firstSlice = lastSlice;
        copyToShmSlice(slice);
    }

    debugs(20, 7, "stored " << bufWritten << '/' << totalWritten << " header bytes of " << *entry);
}