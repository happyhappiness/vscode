    }

    debugs(90, 3, "quick-abort? YES default");
    return true;
}

void
store_client::dumpStats(MemBuf * output, int clientNumber) const
{
    if (_callback.pending())
        return;

    output->appendf("\tClient #%d, %p\n", clientNumber, _callback.callback_data);
    output->appendf("\t\tcopy_offset: %" PRId64 "\n", copyInto.offset);
    output->appendf("\t\tcopy_size: %" PRIuSIZE "\n", copyInto.length);
    output->append("\t\tflags:", 8);

    if (flags.disk_io_pending)
        output->append(" disk_io_pending", 16);

    if (flags.store_copying)
        output->append(" store_copying", 14);

    if (flags.copy_event_pending)
        output->append(" copy_event_pending", 19);

    output->append("\n",1);
}

bool
store_client::Callback::pending() const
{
    return callback_handler && callback_data;
