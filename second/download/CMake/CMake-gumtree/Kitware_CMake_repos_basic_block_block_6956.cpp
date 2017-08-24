{
  struct Curl_easy *data = NULL;

  if(!context)
    return;

  data = (struct Curl_easy *)context;

  infof(data, "%s", line);
  (void) level;
}