             "%s%c%s%c", filename, '\0',  mode, '\0');
    sbytes = 4 + strlen(filename) + strlen(mode);

    /* add tsize option */
    if(data->set.upload && (data->state.infilesize != -1))
      snprintf(buf, sizeof(buf), "%" CURL_FORMAT_CURL_OFF_T,
               data->state.infilesize);
    else
      strcpy(buf, "0"); /* the destination is large enough */

    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes,
                              TFTP_OPTION_TSIZE);
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes, buf);
    /* add blksize option */
    snprintf( buf, sizeof(buf), "%d", state->requested_blksize );
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes,
                              TFTP_OPTION_BLKSIZE);
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes, buf );

    /* add timeout option */
    snprintf( buf, sizeof(buf), "%d", state->retry_time);
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes,
                              TFTP_OPTION_INTERVAL);
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes, buf );

    /* the typecase for the 3rd argument is mostly for systems that do
       not have a size_t argument, like older unixes that want an 'int' */
