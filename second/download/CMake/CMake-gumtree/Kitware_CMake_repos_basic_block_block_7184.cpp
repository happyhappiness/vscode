{
        failf(data,
              "schannel: CertGetNameString did not provide any "
              "certificate name information");
        result = CURLE_PEER_FAILED_VERIFICATION;
      }