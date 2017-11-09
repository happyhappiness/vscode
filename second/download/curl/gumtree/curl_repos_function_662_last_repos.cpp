static void splayprint(struct Curl_tree * t, int d, char output)
{
  struct Curl_tree *node;
  int i;
  int count;
  if(t == NULL)
    return;

  splayprint(t->larger, d + 1, output);
  for(i = 0; i<d; i++)
    if(output)
      printf("  ");

  if(output) {
    printf("%ld.%ld[%d]", (long)t->key.tv_sec,
           (long)t->key.tv_usec, i);
  }

  for(count = 0, node = t->samen; node != t; node = node->samen, count++)
    ;

  if(output) {
    if(count)
      printf(" [%d more]\n", count);
    else
      printf("\n");
  }

  splayprint(t->smaller, d + 1, output);
}