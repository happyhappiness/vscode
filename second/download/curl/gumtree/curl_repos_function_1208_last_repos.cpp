static CURLcode libssh2_session_error_to_CURLE(int err)
{
  switch(err) {
    /* Ordered by order of appearance in libssh2.h */
    case LIBSSH2_ERROR_NONE:
      return CURLE_OK;

    case LIBSSH2_ERROR_SOCKET_NONE:
      return CURLE_COULDNT_CONNECT;

    case LIBSSH2_ERROR_ALLOC:
      return CURLE_OUT_OF_MEMORY;

    case LIBSSH2_ERROR_SOCKET_SEND:
      return CURLE_SEND_ERROR;

    case LIBSSH2_ERROR_HOSTKEY_INIT:
    case LIBSSH2_ERROR_HOSTKEY_SIGN:
    case LIBSSH2_ERROR_PUBLICKEY_UNRECOGNIZED:
    case LIBSSH2_ERROR_PUBLICKEY_UNVERIFIED:
      return CURLE_PEER_FAILED_VERIFICATION;

    case LIBSSH2_ERROR_PASSWORD_EXPIRED:
      return CURLE_LOGIN_DENIED;

    case LIBSSH2_ERROR_SOCKET_TIMEOUT:
    case LIBSSH2_ERROR_TIMEOUT:
      return CURLE_OPERATION_TIMEDOUT;

    case LIBSSH2_ERROR_EAGAIN:
      return CURLE_AGAIN;
  }

  /* TODO: map some more of the libssh2 errors to the more appropriate CURLcode
     error code, and possibly add a few new SSH-related one. We must however
     not return or even depend on libssh2 errors in the public libcurl API */

  return CURLE_SSH;
}