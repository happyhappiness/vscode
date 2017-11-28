void
ConnStateData::clientMaybeReadData(int do_next_read)
{
    if (do_next_read) {
        flags.readMoreRequests = true;
        readSomeData();
    }
}