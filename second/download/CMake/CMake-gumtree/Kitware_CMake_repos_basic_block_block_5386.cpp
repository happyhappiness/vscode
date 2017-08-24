{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct smb_request *req = data->req.protop;
  char *path;
  char *slash;

  /* URL decode the path */
  result = Curl_urldecode(data, data->state.path, 0, &path, NULL, TRUE);
  if(result)
    return result;

  /* Parse the path for the share */
  req->share = strdup((*path == '/' || *path == '\\') ? path + 1 : path);
  if(!req->share) {
    free(path);

    return CURLE_OUT_OF_MEMORY;
  }

  slash = strchr(req->share, '/');
  if(!slash)
    slash = strchr(req->share, '\\');

  /* The share must be present */
  if(!slash) {
    free(path);

    return CURLE_URL_MALFORMAT;
  }

  /* Parse the path for the file path converting any forward slashes into
     backslashes */
  *slash++ = 0;
  req->path = slash;
  for(; *slash; slash++) {
    if(*slash == '/')
      *slash = '\\';
  }

  free(path);

  return CURLE_OK;
}