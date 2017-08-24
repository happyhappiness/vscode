{
    /* Now we need to make sure that if there is a name appearing more than
       once, the longest specified path version comes first. To make this
       the swiftest way, we just sort them all based on path length. */
    struct Cookie **array;
    size_t i;

    /* alloc an array and store all cookie pointers */
    array = malloc(sizeof(struct Cookie *) * matches);
    if(!array)
      goto fail;

    co = mainco;

    for(i=0; co; co = co->next)
      array[i++] = co;

    /* now sort the cookie pointers in path length order */
    qsort(array, matches, sizeof(struct Cookie *), cookie_sort);

    /* remake the linked list order according to the new order */

    mainco = array[0]; /* start here */
    for(i=0; i<matches-1; i++)
      array[i]->next = array[i+1];
    array[matches-1]->next = NULL; /* terminate the list */

    free(array); /* remove the temporary data again */
  }