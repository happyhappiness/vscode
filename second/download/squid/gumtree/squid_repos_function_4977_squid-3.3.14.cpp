int
Fs::Ufs::UFSSwapLogParser::SwapLogEntries()
{
    struct stat sb;

    if (log_entries >= 0)
        return log_entries;

    if (log && record_size && 0 == fstat(fileno(log), &sb)) {
        log_entries = sb.st_size/record_size;
        return log_entries;
    }

    return 0;
}