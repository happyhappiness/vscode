}



#ifdef DEBUGBUILD

void Curl_multi_dump(struct Curl_multi *multi)

{

  struct Curl_easy *data;

  int i;

  fprintf(stderr, "* Multi status: %d handles, %d alive\n",

          multi->num_easy, multi->num_alive);

