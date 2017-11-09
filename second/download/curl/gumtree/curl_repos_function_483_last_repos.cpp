static void remove_handles(void)
{
  int i;

  for(i = 0; i < num_handles; i++) {
    if(handles[i])
      curl_easy_cleanup(handles[i]);
  }
}