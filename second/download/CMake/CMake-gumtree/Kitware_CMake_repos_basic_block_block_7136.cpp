{
    bool isWin2k = Curl_verify_windows_version(5, 0, PLATFORM_WINNT,
                                               VERSION_EQUAL);

    if(isWin2k && sspi_status == SEC_E_OK)
      connssl->recv_sspi_close_notify = true;
    else {
      *err = CURLE_RECV_ERROR;
      infof(data, "schannel: server closed abruptly (missing close_notify)\n");
    }
  }