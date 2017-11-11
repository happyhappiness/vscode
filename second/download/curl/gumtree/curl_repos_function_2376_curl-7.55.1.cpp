CF_INLINE CFStringRef CopyCertSubject(SecCertificateRef cert)
{
  CFStringRef server_cert_summary = CFSTR("(null)");

#if CURL_BUILD_IOS
  /* iOS: There's only one way to do this. */
  server_cert_summary = SecCertificateCopySubjectSummary(cert);
#else
#if CURL_BUILD_MAC_10_7
  /* Lion & later: Get the long description if we can. */
  if(SecCertificateCopyLongDescription != NULL)
    server_cert_summary =
      SecCertificateCopyLongDescription(NULL, cert, NULL);
  else
#endif /* CURL_BUILD_MAC_10_7 */
#if CURL_BUILD_MAC_10_6
  /* Snow Leopard: Get the certificate summary. */
  if(SecCertificateCopySubjectSummary != NULL)
    server_cert_summary = SecCertificateCopySubjectSummary(cert);
  else
#endif /* CURL_BUILD_MAC_10_6 */
  /* Leopard is as far back as we go... */
  (void)SecCertificateCopyCommonName(cert, &server_cert_summary);
#endif /* CURL_BUILD_IOS */
  return server_cert_summary;
}