{
    /* Append the algorithm */
    tmp = aprintf("%s, algorithm=\"%s\"", response, digest->algorithm);
    free(response);
    if(!tmp)
      return CURLE_OUT_OF_MEMORY;

    response = tmp;
  }