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
