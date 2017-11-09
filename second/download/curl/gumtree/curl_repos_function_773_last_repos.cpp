void fuzz_terminate_fuzz_data(FUZZ_DATA *fuzz)
{
  fuzz_free((void **)&fuzz->url);
  fuzz_free((void **)&fuzz->username);
  fuzz_free((void **)&fuzz->password);
  fuzz_free((void **)&fuzz->postfields);
  fuzz_free((void **)&fuzz->cookie);
  fuzz_free((void **)&fuzz->range);
  fuzz_free((void **)&fuzz->customrequest);
  fuzz_free((void **)&fuzz->mail_from);

  if(fuzz->header_list != NULL) {
    curl_slist_free_all(fuzz->header_list);
    fuzz->header_list = NULL;
  }

  if(fuzz->mail_recipients_list != NULL) {
    curl_slist_free_all(fuzz->mail_recipients_list);
    fuzz->mail_recipients_list = NULL;
  }

  if(fuzz->easy != NULL) {
    curl_easy_cleanup(fuzz->easy);
    fuzz->easy = NULL;
  }
}