void
Ipc::Mem::Segment::lock()
{
    if (!Config.shmLocking) {
        debugs(54, 5, "mlock(2)-ing disabled");
        return;
    }

#if defined(_POSIX_MEMLOCK_RANGE)
    debugs(54, 7, "mlock(" << theName << ',' << theSize << ") starts");
    if (mlock(theMem, theSize) != 0) {
        const int savedError = errno;
        fatalf("shared_memory_locking on but failed to mlock(%s, %" PRId64 "): %s\n",
               theName.termedBuf(),static_cast<int64_t>(theSize), xstrerr(savedError));
    }
    // TODO: Warn if it took too long.
    debugs(54, 7, "mlock(" << theName << ',' << theSize << ") OK");
#else
    debugs(54, 5, "insufficient mlock(2) support");
    if (Config.shmLocking.configured()) { // set explicitly
        static bool warnedOnce = false;
        if (!warnedOnce) {
            debugs(54, DBG_IMPORTANT, "ERROR: insufficient mlock(2) support prevents " <<
                   "honoring `shared_memory_locking on`. " <<
                   "If you lack RAM, kernel will kill Squid later.");
            warnedOnce = true;
        }
    }
#endif
}