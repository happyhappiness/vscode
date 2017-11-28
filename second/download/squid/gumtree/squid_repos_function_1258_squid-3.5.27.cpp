void
Mem::Stats(StoreEntry * sentry)
{
    StoreEntryStream stream(sentry);
    Report(stream);
    memStringStats(stream);
    memBufStats(stream);
#if WITH_VALGRIND
    if (RUNNING_ON_VALGRIND) {
        long int leaked = 0, dubious = 0, reachable = 0, suppressed = 0;
        stream << "Valgrind Report:\n";
        stream << "Type\tAmount\n";
        debugs(13, DBG_IMPORTANT, "Asking valgrind for memleaks");
        VALGRIND_DO_LEAK_CHECK;
        debugs(13, DBG_IMPORTANT, "Getting valgrind statistics");
        VALGRIND_COUNT_LEAKS(leaked, dubious, reachable, suppressed);
        stream << "Leaked\t" << leaked << "\n";
        stream << "Dubious\t" << dubious << "\n";
        stream << "Reachable\t" << reachable << "\n";
        stream << "Suppressed\t" << suppressed << "\n";
    }
#endif
    stream.flush();
}