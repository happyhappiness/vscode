f(SSL_GetCipherSuiteInfo(channel.cipherSuite,
                              &suite, sizeof suite) == SECSuccess) {
      infof(conn->data, "SSL connection using %s\n", suite.cipherSuiteName);
    }