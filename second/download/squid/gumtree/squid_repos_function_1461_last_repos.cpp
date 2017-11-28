void
fdDumpOpen(void)
{
    int i;
    fde *F;

    for (i = 0; i < Squid_MaxFD; ++i) {
        F = &fd_table[i];

        if (!F->flags.open)
            continue;

        if (i == fileno(debug_log))
            continue;

        debugs(51, DBG_IMPORTANT, "Open FD "<< std::left<< std::setw(10) <<
               (F->bytes_read && F->bytes_written ? "READ/WRITE" :
                F->bytes_read ? "READING" : F->bytes_written ? "WRITING" :
                "UNSTARTED")  <<
               " "<< std::right << std::setw(4) << i  << " " << F->desc);
    }
}