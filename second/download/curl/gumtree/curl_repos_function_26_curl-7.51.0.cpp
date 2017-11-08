static void check_multi_info(void)
{
  int running_handles;
  char *done_url;
  CURLMsg *message;
  int pending;
  FILE *file;

  while((message = curl_multi_info_read(curl_handle, &pending))) {
    switch(message->msg) {
    case CURLMSG_DONE:
      curl_easy_getinfo(message->easy_handle, CURLINFO_EFFECTIVE_URL,
                        &done_url);
      curl_easy_getinfo(message->easy_handle, CURLINFO_PRIVATE, &file);
      printf("%s DONE\n", done_url);

      curl_multi_remove_handle(curl_handle, message->easy_handle);
      curl_easy_cleanup(message->easy_handle);
      if(file) {
        fclose(file);
      }
      break;

    default:
      fprintf(stderr, "CURLMSG default\n");
      break;
    }
  }
}