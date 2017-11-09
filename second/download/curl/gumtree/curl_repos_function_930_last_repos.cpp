CURLcode tool_setopt_mimepost(CURL *curl, struct GlobalConfig *config,
                              const char *name, CURLoption tag,
                              curl_mime *mimepost)
{
  CURLcode ret = CURLE_OK;

  ret = curl_easy_setopt(curl, tag, mimepost);

  if(config->libcurl && mimepost && !ret) {
    int i;

    ret = libcurl_generate_mime(mimepost, &i);

    if(!ret)
      CODE2("curl_easy_setopt(hnd, %s, mime%d);", name, i);
  }

nomem:
  return ret;
}