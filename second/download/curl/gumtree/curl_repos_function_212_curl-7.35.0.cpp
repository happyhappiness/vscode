static void addsock(curl_socket_t s, CURL *easy, int action, GlobalInfo *g)
{
  int *fdp = (int *)calloc(sizeof(int), 1); /* fdp is used to store current action */

  setsock(fdp, s, easy, action, g);
  curl_multi_assign(g->multi, s, fdp);
}