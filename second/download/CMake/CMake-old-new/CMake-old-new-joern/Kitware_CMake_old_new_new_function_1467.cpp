void Curl_scan_cache_used(void *user, void *ptr)
{
  struct Curl_dns_entry *e = ptr;
  (void)user; /* prevent compiler warning */
  if(e->inuse) {
    fprintf(stderr, "*** WARNING: locked DNS cache entry detected: %s\n",
            e->entry_id);
    /* perform a segmentation fault to draw attention */
    *(void **)0 = 0;
  }
}