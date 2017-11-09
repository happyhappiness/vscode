int tpf_select_libcurl(int maxfds, fd_set *reads, fd_set *writes,
                       fd_set *excepts, struct timeval *tv)
{
   int rc;

   rc = tpf_select_bsd(maxfds, reads, writes, excepts, tv);
   tpf_process_signals();
   return rc;
}