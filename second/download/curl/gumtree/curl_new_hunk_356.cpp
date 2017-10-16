  if(data)
    free(convbuf);
#endif
  return strlen(base64data); /* return the length of the new data */
}
/* ---- End of Base64 Encoding ---- */
