void
store_client::dumpStats(MemBuf * output, int clientNumber) const
{
    if (_callback.pending())
        return;

    output->Printf("\tClient #%d, %p\n", clientNumber, _callback.callback_data);

    output->Printf("\t\tcopy_offset: %" PRId64 "\n",
                   copyInto.offset);

    output->Printf("\t\tcopy_size: %d\n",
                   (int) copyInto.length);

    output->Printf("\t\tflags:");

    if (flags.disk_io_pending)
        output->Printf(" disk_io_pending");

    if (flags.store_copying)
        output->Printf(" store_copying");

    if (flags.copy_event_pending)
        output->Printf(" copy_event_pending");

    output->Printf("\n");
}