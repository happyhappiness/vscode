{
    PR_Init(PR_USER_THREAD, PR_PRIORITY_NORMAL, 256);
    nss_initlock = PR_NewLock();
    nss_crllock = PR_NewLock();
    nss_findslot_lock = PR_NewLock();
    nss_trustload_lock = PR_NewLock();
  }