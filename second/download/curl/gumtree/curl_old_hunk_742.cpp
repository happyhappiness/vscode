    free(ci->certinfo); /* free the actual array too */
    ci->certinfo = NULL;
    ci->num_of_certs = 0;
  }
}

#if defined(USE_SSLEAY) || defined(USE_GNUTLS) || defined(USE_NSS) || \
    defined(USE_DARWINSSL)
/* these functions are only used by some SSL backends */

void Curl_ssl_random(struct SessionHandle *data,
                     unsigned char *entropy,
                     size_t length)
{
  curlssl_random(data, entropy, length);
}

void Curl_ssl_md5sum(unsigned char *tmp, /* input */
                     size_t tmplen,
                     unsigned char *md5sum, /* output */
                     size_t md5len)
{
  curlssl_md5sum(tmp, tmplen, md5sum, md5len);
}
#endif /* USE_SSLEAY || USE_GNUTLS || USE_NSS || USE_DARWINSSL */

#endif /* USE_SSL */
