snprintf((char *)ptr + NTLM_HMAC_MD5_LEN, NTLMv2_BLOB_LEN,
           "%c%c%c%c"   /* NTLMv2_BLOB_SIGNATURE */
           "%c%c%c%c",  /* Reserved = 0 */
           NTLMv2_BLOB_SIGNATURE[0], NTLMv2_BLOB_SIGNATURE[1],
           NTLMv2_BLOB_SIGNATURE[2], NTLMv2_BLOB_SIGNATURE[3],
           0, 0, 0, 0);