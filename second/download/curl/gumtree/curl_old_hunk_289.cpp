    300, 220, 80, 90, 50, 100, 60, 200, 120, 300, 400, 200, 256, 122, 60, 120,
    200, 300, 220, 80, 90};
  int i;
  root = NULL;              /* the empty tree */

  for (i = 0; i < MAX; i++) {
    int key;
    ptrs[i] = t = (struct Curl_tree *)malloc(sizeof(struct Curl_tree));

#ifdef TEST2
    key = sizes[i];
#elif defined(TEST1)
    key = (541*i)%1023;
#elif defined(TEST3)
    key = 100;
#endif

    t->payload = (void *)key; /* for simplicity */
    if(!t) {
      puts("out of memory!");
      return 0;
    }
    root = Curl_splayinsert(key, root, t);
  }
