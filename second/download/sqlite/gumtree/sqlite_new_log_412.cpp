sqlite3_log(SQLITE_NOTICE_RECOVER_ROLLBACK, "recovered %d pages from %s",
                nPlayback, pPager->zJournal);