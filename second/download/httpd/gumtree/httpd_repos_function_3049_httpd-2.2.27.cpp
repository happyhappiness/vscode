static apr_status_t md5_update_buffer(apr_md5_ctx_t *context,
                                      const void *vinput,
                                      apr_size_t inputLen,
                                      int xlate_buffer)
{
    const unsigned char *input = vinput;
    unsigned int i, idx, partLen;
#if APR_HAS_XLATE
    apr_size_t inbytes_left, outbytes_left;
#endif

    /* Compute number of bytes mod 64 */
    idx = (unsigned int)((context->count[0] >> 3) & 0x3F);

    /* Update number of bits */
    if ((context->count[0] += ((apr_uint32_t)inputLen << 3)) 
            < ((apr_uint32_t)inputLen << 3))
        context->count[1]++;
    context->count[1] += (apr_uint32_t)inputLen >> 29;

    partLen = 64 - idx;

    /* Transform as many times as possible. */
#if !APR_HAS_XLATE
    if (inputLen >= partLen) {
        memcpy(&context->buffer[idx], input, partLen);
        MD5Transform(context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5Transform(context->state, &input[i]);

        idx = 0;
    }
    else
        i = 0;

    /* Buffer remaining input */
    memcpy(&context->buffer[idx], &input[i], inputLen - i);
#else /*APR_HAS_XLATE*/
    if (inputLen >= partLen) {
        if (context->xlate && (xlate_buffer == DO_XLATE)) {
            inbytes_left = outbytes_left = partLen;
            apr_xlate_conv_buffer(context->xlate, (const char *)input, 
                                  &inbytes_left,
                                  (char *)&context->buffer[idx], 
                                  &outbytes_left);
        }
        else {
            memcpy(&context->buffer[idx], input, partLen);
        }
        MD5Transform(context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64) {
            if (context->xlate && (xlate_buffer == DO_XLATE)) {
                unsigned char inp_tmp[64];
                inbytes_left = outbytes_left = 64;
                apr_xlate_conv_buffer(context->xlate, (const char *)&input[i], 
                                      &inbytes_left, (char *)inp_tmp, 
                                      &outbytes_left);
                MD5Transform(context->state, inp_tmp);
            }
            else {
                MD5Transform(context->state, &input[i]);
            }
        }

        idx = 0;
    }
    else
        i = 0;

    /* Buffer remaining input */
    if (context->xlate && (xlate_buffer == DO_XLATE)) {
        inbytes_left = outbytes_left = inputLen - i;
        apr_xlate_conv_buffer(context->xlate, (const char *)&input[i], 
                              &inbytes_left, (char *)&context->buffer[idx], 
                              &outbytes_left);
    }
    else {
        memcpy(&context->buffer[idx], &input[i], inputLen - i);
    }
#endif /*APR_HAS_XLATE*/
    return APR_SUCCESS;
}