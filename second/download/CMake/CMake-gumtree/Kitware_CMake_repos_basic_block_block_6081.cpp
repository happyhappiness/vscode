{
    /* We have an options list in the URL so decode it */
    char *newoptions;
    result = Curl_urldecode(data, optionsp, 0, &newoptions, NULL, FALSE);
    if(result) {
      goto out;
    }

    free(*options);
    *options = newoptions;
  }