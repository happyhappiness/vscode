{
    dtd->scaffIndex = (int *)MALLOC(groupSize * sizeof(int));
    if (!dtd->scaffIndex)
      return -1;
    dtd->scaffIndex[0] = 0;
  }