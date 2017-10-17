
  if( rc==SQLITE_OK ){
    zMaster = pPager->pTmpSpace;
    rc = readMasterJournal(pPager->jfd, zMaster, pPager->pVfs->mxPathname+1);
    testcase( rc!=SQLITE_OK );
  }
  if( rc==SQLITE_OK
   && (pPager->eState>=PAGER_WRITER_DBMOD || pPager->eState==PAGER_OPEN)
  ){
    rc = sqlite3PagerSync(pPager, 0);
  }
  if( rc==SQLITE_OK ){
    rc = pager_end_transaction(pPager, zMaster[0]!='\0', 0);
    testcase( rc!=SQLITE_OK );
  }
  if( rc==SQLITE_OK && zMaster[0] && res ){
    /* If there was a master journal and this routine will return success,
    ** see if it is possible to delete the master journal.
    */
    rc = pager_delmaster(pPager, zMaster);
    testcase( rc!=SQLITE_OK );
  }
  if( isHot && nPlayback ){
    sqlite3_log(SQLITE_NOTICE_RECOVER_ROLLBACK, "recovered %d pages from %s",
                nPlayback, pPager->zJournal);
  }

  /* The Pager.sectorSize variable may have been updated while rolling
  ** back a journal created by a process with a different sector size
  ** value. Reset it to the correct value for this process.
  */
  setSectorSize(pPager);
