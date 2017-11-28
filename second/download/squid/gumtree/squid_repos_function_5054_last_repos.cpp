void
Rock::HeaderUpdater::readMore(const char *why)
{
    debugs(47, 7, "from " << bytesRead << " because " << why);
    Must(reader);
    readerBuffer.clear();
    storeRead(reader,
              readerBuffer.rawSpace(store->slotSize),
              store->slotSize,
              bytesRead,
              &NoteRead,
              this);
}