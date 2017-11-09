int Curl_debug(struct Curl_easy *data, curl_infotype type,
               char *ptr, size_t size,
               struct connectdata *conn)
{
  int rc;
  if(data->set.printhost && conn && conn->host.dispname) {
    char buffer[160];
    const char *t = NULL;
    const char *w = "Data";
    switch(type) {
    case CURLINFO_HEADER_IN:
      w = "Header";
      /* FALLTHROUGH */
    case CURLINFO_DATA_IN:
      t = "from";
      break;
    case CURLINFO_HEADER_OUT:
      w = "Header";
      /* FALLTHROUGH */
    case CURLINFO_DATA_OUT:
      t = "to";
      break;
    default:
      break;
    }

    if(t) {
      snprintf(buffer, sizeof(buffer), "[%s %s %s]", w, t,
               conn->host.dispname);
      rc = showit(data, CURLINFO_TEXT, buffer, strlen(buffer));
      if(rc)
        return rc;
    }
  }
  rc = showit(data, type, ptr, size);
  return rc;
}