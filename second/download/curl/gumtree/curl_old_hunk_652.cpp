          my_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, FALSE);
          my_setopt(curl, CURLOPT_HTTP_TRANSFER_DECODING, FALSE);
        }

        /* curl 7.17.1 */
        if(!config->nokeepalive) {
          my_setopt(curl, CURLOPT_SOCKOPTFUNCTION, tool_sockopt_cb);
          my_setopt(curl, CURLOPT_SOCKOPTDATA, config);
        }

        /* curl 7.20.0 */
        if(config->tftp_blksize)
          my_setopt(curl, CURLOPT_TFTP_BLKSIZE, config->tftp_blksize);

        if(config->mail_from)
          my_setopt_str(curl, CURLOPT_MAIL_FROM, config->mail_from);

        if(config->mail_rcpt)
          my_setopt(curl, CURLOPT_MAIL_RCPT, config->mail_rcpt);

        /* curl 7.20.x */
        if(config->ftp_pret)
          my_setopt(curl, CURLOPT_FTP_USE_PRET, TRUE);

        if(config->proto_present)
          my_setopt(curl, CURLOPT_PROTOCOLS, config->proto);
        if(config->proto_redir_present)
          my_setopt(curl, CURLOPT_REDIR_PROTOCOLS, config->proto_redir);

        if((urlnode->flags & GETOUT_USEREMOTE)
           && config->content_disposition) {
          my_setopt(curl, CURLOPT_HEADERFUNCTION, tool_header_cb);
          my_setopt(curl, CURLOPT_HEADERDATA, &outs);
        }
