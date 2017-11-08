void Curl_splayprint(struct Curl_tree * t, int d, char output)
{
  struct Curl_tree *node;
  int i;
  int count;
  if(t == NULL)
    return;

  Curl_splayprint(t->larger, d+1, output);
  for (i=0; i<d; i++)
    if(output)
      printf("  ");

  if(output) {
    printf("%d[%d]", t->key, i);
  }

  for(count=0, node = t->same; node; node = node->same, count++)
    ;

  if(output) {
    if(count)
      printf(" [%d more]\n", count);
    else
      printf("\n");
  }

  Curl_splayprint(t->smaller, d+1, output);
}