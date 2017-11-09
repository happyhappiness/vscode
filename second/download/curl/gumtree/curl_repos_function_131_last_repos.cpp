int main(void)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, "user");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "secret");

    /* This is source mailbox folder to select */
    curl_easy_setopt(curl, CURLOPT_URL, "imap://imap.example.com/INBOX");

    /* Set the COPY command specifying the message ID and destination folder */
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "COPY 1 FOLDER");

    /* Note that to perform a move operation you will need to perform the copy,
     * then mark the original mail as Deleted and EXPUNGE or CLOSE. Please see
     * imap-store.c for more information on deleting messages. */

    /* Perform the custom request */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* Always cleanup */
    curl_easy_cleanup(curl);
  }

  return (int)res;
}