static CURLcode ssh_getworkingpath(struct connectdata *conn,
                                   char *homedir,  /* when SFTP is used */
                                   char **path) /* returns the  allocated
                                                   real path to work with */
{
  struct Curl_easy *data = conn->data;
  char *real_path = NULL;
  char *working_path;
  size_t working_path_len;
  CURLcode result =
    Curl_urldecode(data, data->state.path, 0, &working_path,
                   &working_path_len, FALSE);
  if(result)
    return result;

  /* Check for /~/, indicating relative to the user's home directory */
  if(conn->handler->protocol & CURLPROTO_SCP) {
    real_path = malloc(working_path_len + 1);
    if(real_path == NULL) {
      free(working_path);
      return CURLE_OUT_OF_MEMORY;
    }
    if((working_path_len > 3) && (!memcmp(working_path, "/~/", 3)))
      /* It is referenced to the home directory, so strip the leading '/~/' */
      memcpy(real_path, working_path + 3, 4 + working_path_len-3);
    else
      memcpy(real_path, working_path, 1 + working_path_len);
  }
  else if(conn->handler->protocol & CURLPROTO_SFTP) {
    if((working_path_len > 1) && (working_path[1] == '~')) {
      size_t homelen = strlen(homedir);
      real_path = malloc(homelen + working_path_len + 1);
      if(real_path == NULL) {
        free(working_path);
        return CURLE_OUT_OF_MEMORY;
      }
      /* It is referenced to the home directory, so strip the
         leading '/' */
      memcpy(real_path, homedir, homelen);
      real_path[homelen] = '/';
      real_path[homelen + 1] = '\0';
      if(working_path_len > 3) {
        memcpy(real_path + homelen + 1, working_path + 3,
               1 + working_path_len -3);
      }
    }
    else {
      real_path = malloc(working_path_len + 1);
      if(real_path == NULL) {
        free(working_path);
        return CURLE_OUT_OF_MEMORY;
      }
      memcpy(real_path, working_path, 1 + working_path_len);
    }
  }

  free(working_path);

  /* store the pointer for the caller to receive */
  *path = real_path;

  return CURLE_OK;
}