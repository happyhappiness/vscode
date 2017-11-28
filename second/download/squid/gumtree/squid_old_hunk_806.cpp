    if (fd < 0) {
        debugs(50, DBG_IMPORTANT, "ERROR: while opening swap log" << new_path << ": " << xstrerror());
        fatalf("Failed to open swap log %s", new_path);
    }

    swaplog_fd = fd;

    {
        const StoreSwapLogHeader header;
        MemBuf buf;
        buf.init(header.record_size, header.record_size);
        buf.append(reinterpret_cast<const char*>(&header), sizeof(header));
