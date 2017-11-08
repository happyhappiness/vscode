static const char *tls_rt_type(int type)
{
  return (
    type == SSL3_RT_CHANGE_CIPHER_SPEC ? "TLS change cipher, " :
    type == SSL3_RT_ALERT              ? "TLS alert, "         :
    type == SSL3_RT_HANDSHAKE          ? "TLS handshake, "     :
    type == SSL3_RT_APPLICATION_DATA   ? "TLS app data, "      :
                                         "TLS Unknown, ");
}