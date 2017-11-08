char *
Curl_SSL_Strerror_a(int sslreturnvalue, SSLErrorMsg * serrmsgp)

{
  return set_thread_string(LK_SSL_ERROR,
                           SSL_Strerror(sslreturnvalue, serrmsgp));
}