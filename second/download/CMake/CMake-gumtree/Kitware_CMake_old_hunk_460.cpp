}



#ifdef DEBUGBUILD

void Curl_multi_dump(const struct Curl_multi *multi_handle)

{

  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;

  struct SessionHandle *data;

  int i;

  fprintf(stderr, "* Multi status: %d handles, %d alive\n",

          multi->num_easy, multi->num_alive);

