  return snprintf(p, len, " nghttp2/%s", h2->version_str);

}



/* HTTP/2 error code to name based on the Error Code Registry.

https://tools.ietf.org/html/rfc7540#page-77

nghttp2_error_code enums are identical.

*/

const char *Curl_http2_strerror(uint32_t err) {

#ifndef NGHTTP2_HAS_HTTP2_STRERROR

  const char *str[] = {

    "NO_ERROR",             /* 0x0 */

    "PROTOCOL_ERROR",       /* 0x1 */

    "INTERNAL_ERROR",       /* 0x2 */

    "FLOW_CONTROL_ERROR",   /* 0x3 */

    "SETTINGS_TIMEOUT",     /* 0x4 */

    "STREAM_CLOSED",        /* 0x5 */

    "FRAME_SIZE_ERROR",     /* 0x6 */

    "REFUSED_STREAM",       /* 0x7 */

    "CANCEL",               /* 0x8 */

    "COMPRESSION_ERROR",    /* 0x9 */

    "CONNECT_ERROR",        /* 0xA */

    "ENHANCE_YOUR_CALM",    /* 0xB */

    "INADEQUATE_SECURITY",  /* 0xC */

    "HTTP_1_1_REQUIRED"     /* 0xD */

  };

  return (err < sizeof str / sizeof str[0]) ? str[err] : "unknown";

#else

  return nghttp2_http2_strerror(err);

#endif

}



/*

 * The implementation of nghttp2_send_callback type. Here we write |data| with

 * size |length| to the network and return the number of bytes actually

