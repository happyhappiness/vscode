int main(void)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, "user");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "secret");

    /* This is the mailbox folder to select */
    curl_easy_setopt(curl, CURLOPT_URL, "imap://imap.example.com/INBOX");

    /* Set the STORE command with the Deleted flag for message 1. Note that
     * you can use the STORE command to set other flags such as Seen, Answered,
     * Flagged, Draft and Recent. */
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "STORE 1 +Flags \\Deleted");

    /* Perform the custom request */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    else {
      /* Set the EXPUNGE command, although you can use the CLOSE command if you
       * don't want to know the result of the STORE */
      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "EXPUNGE");

      /* Perform the second custom request */
      res = curl_easy_perform(curl);

      /* Check for errors */
      if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }

    /* Always cleanup */
    curl_easy_cleanup(curl);
  }

  return (int)res;
}