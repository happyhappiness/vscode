void url_fclose(URL_FILE *file)
{
  /* make sure the easy handle is not in the multi handle anymore */
  curl_multi_remove_handle(multi_handle, file->handle.curl);

  /* cleanup */
  curl_easy_cleanup(file->handle.curl);
}