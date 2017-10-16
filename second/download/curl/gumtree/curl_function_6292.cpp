int main(int argc, argv_item_t argv[])
{
  struct Curl_tree *root, *t;
  void *ptrs[MAX];
  int adds=0;
  int rc;

  static const long sizes[]={
    50, 60, 50, 100, 60, 200, 120, 300, 400, 200, 256, 122, 60, 120, 200, 300,
    220, 80, 90, 50, 100, 60, 200, 120, 300, 400, 200, 256, 122, 60, 120, 200,
    300, 220, 80, 90, 50, 100, 60, 200, 120, 300, 400, 200, 256, 122, 60, 120,
    200, 300, 220, 80, 90};
  int i;
  root = NULL;              /* the empty tree */

  for (i = 0; i < MAX; i++) {
    struct timeval key;
    ptrs[i] = t = malloc(sizeof(struct Curl_tree));
    if(!t) {
      puts("out of memory!");
      return 0;
    }

    key.tv_sec = 0;
#ifdef TEST2
    key.tv_usec = sizes[i];
#elif defined(TEST1)
    key.tv_usec = (541*i)%1023;
#elif defined(TEST3)
    key.tv_usec = 100;
#endif

    t->payload = (void *)key.tv_usec; /* for simplicity */
    root = Curl_splayinsert(key, root, t);
  }

#if 0
  puts("Result:");
  Curl_splayprint(root, 0, 1);
#endif

#if 1
  for (i = 0; i < MAX; i++) {
    int rem = (i+7)%MAX;
    struct Curl_tree *r;
    printf("Tree look:\n");
    Curl_splayprint(root, 0, 1);
    printf("remove pointer %d, payload %ld\n", rem,
           (long)((struct Curl_tree *)ptrs[rem])->payload);
    rc = Curl_splayremovebyaddr(root, (struct Curl_tree *)ptrs[rem], &root);
    if(rc)
      /* failed! */
      printf("remove %d failed!\n", rem);
  }
#endif

  return 0;
}