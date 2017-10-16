  }
#endif

  if(!outs->stream && !tool_create_output_file(outs))
    return failure;

  rc = fwrite(buffer, sz, nmemb, outs->stream);

  if((sz * nmemb) == rc)
    /* we added this amount of data to the output */
    outs->bytes += (sz * nmemb);

  if(config->readbusy) {
    config->readbusy = FALSE;
    curl_easy_pause(config->easy, CURLPAUSE_CONT);
  }

