int main(int argc, char **argv)
{
  CURL *curl;
  CURLcode res;

  struct HttpPost *formpost=NULL;
  struct HttpPost *lastptr=NULL;

  /* Fill in the file upload field */
  curl_formparse("sendfile=@foo",
                 &formpost,
                 &lastptr);

  /* Fill in the filename field */
  curl_formparse("filename=foo",
                 &formpost,
                 &lastptr);
  

  /* Fill in the submit field too, even if this is rarely needed */
  curl_formparse("submit=send",
                 &formpost,
                 &lastptr);

  curl = curl_easy_init();
  if(curl) {
    /* what URL that receives this POST */
    curl_easy_setopt(curl, CURLOPT_URL, "http://curl.haxx.se/examplepost.cgi");
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);

    /* then cleanup the formpost chain */
    curl_formfree(formpost);
  }
  return 0;
}