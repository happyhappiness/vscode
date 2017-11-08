static CURLcode libssh2_session_error_to_CURLE(int err)
{
  if(err == LIBSSH2_ERROR_ALLOC)
    return CURLE_OUT_OF_MEMORY;

  /* TODO: map some more of the libssh2 errors to the more appropriate CURLcode
     error code, and possibly add a few new SSH-related one. We must however
     not return or even depend on libssh2 errors in the public libcurl API */

  return CURLE_SSH;
}