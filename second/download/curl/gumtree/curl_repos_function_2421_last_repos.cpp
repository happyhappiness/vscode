static CURLcode Curl_mbedtls_random(struct Curl_easy *data,
                                    unsigned char *entropy, size_t length)
{
#if defined(MBEDTLS_CTR_DRBG_C)
  int ret = -1;
  char errorbuf[128];
  mbedtls_entropy_context ctr_entropy;
  mbedtls_ctr_drbg_context ctr_drbg;
  mbedtls_entropy_init(&ctr_entropy);
  mbedtls_ctr_drbg_init(&ctr_drbg);
  errorbuf[0] = 0;

  ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func,
                              &ctr_entropy, NULL, 0);

  if(ret) {
#ifdef MBEDTLS_ERROR_C
    mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
    failf(data, "Failed - mbedTLS: ctr_drbg_seed returned (-0x%04X) %s\n",
          -ret, errorbuf);
  }
  else {
    ret = mbedtls_ctr_drbg_random(&ctr_drbg, entropy, length);

    if(ret) {
#ifdef MBEDTLS_ERROR_C
      mbedtls_strerror(ret, errorbuf, sizeof(errorbuf));
#endif /* MBEDTLS_ERROR_C */
      failf(data, "mbedTLS: ctr_drbg_init returned (-0x%04X) %s\n",
            -ret, errorbuf);
    }
  }

  mbedtls_ctr_drbg_free(&ctr_drbg);
  mbedtls_entropy_free(&ctr_entropy);

  return ret == 0 ? CURLE_OK : CURLE_FAILED_INIT;
#elif defined(MBEDTLS_HAVEGE_C)
  mbedtls_havege_state hs;
  mbedtls_havege_init(&hs);
  mbedtls_havege_random(&hs, entropy, length);
  mbedtls_havege_free(&hs);
  return CURLE_OK;
#else
  return CURLE_NOT_BUILT_IN;
#endif
}