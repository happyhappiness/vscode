f(SSLCreateContext != NULL)
      CFRelease(connssl->ssl_ctx);
#if CURL_SUPPORT_MAC_10_8
    else
      (void)SSLDisposeContext(connssl->ssl_ctx)