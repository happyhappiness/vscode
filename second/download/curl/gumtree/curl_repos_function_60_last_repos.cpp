int main(void)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */
    curl_easy_setopt(curl, CURLOPT_USERNAME, "user");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "secret");

    /* This is just the server URL */
    curl_easy_setopt(curl, CURLOPT_URL, "imap://imap.example.com");

    /* Set the EXAMINE command specifying the mailbox folder */
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "EXAMINE OUTBOX");

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