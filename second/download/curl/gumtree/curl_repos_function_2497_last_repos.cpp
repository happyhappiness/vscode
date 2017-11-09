static int append_cert_to_array(struct Curl_easy *data,
                                unsigned char *buf, size_t buflen,
                                CFMutableArrayRef array)
{
    CFDataRef certdata = CFDataCreate(kCFAllocatorDefault, buf, buflen);
    char *certp;
    CURLcode result;
    if(!certdata) {
      failf(data, "SSL: failed to allocate array for CA certificate");
      return CURLE_OUT_OF_MEMORY;
    }

    SecCertificateRef cacert =
      SecCertificateCreateWithData(kCFAllocatorDefault, certdata);
    CFRelease(certdata);
    if(!cacert) {
      failf(data, "SSL: failed to create SecCertificate from CA certificate");
      return CURLE_SSL_CACERT;
    }

    /* Check if cacert is valid. */
    result = CopyCertSubject(data, cacert, &certp);
    if(result)
      return result;
    free(certp);

    CFArrayAppendValue(array, cacert);
    CFRelease(cacert);

    return CURLE_OK;
}