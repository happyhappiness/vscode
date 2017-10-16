          my_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, FALSE);
          my_setopt(curl, CURLOPT_HTTP_TRANSFER_DECODING, FALSE);
        }

        /* curl 7.17.1 */
        if(!config->nokeepalive) {
          my_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
          if(config->alivetime != 0) {
#if !defined(TCP_KEEPIDLE) || !defined(TCP_KEEPINTVL)
            warnf(config, "Keep-alive functionality somewhat crippled due to "
                "missing support in your operating system!\n");
#endif
            my_setopt(curl, CURLOPT_TCP_KEEPIDLE, config->alivetime);
            my_setopt(curl, CURLOPT_TCP_KEEPINTVL, config->alivetime);
          }
        }
        else
          my_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L);

        /* curl 7.20.0 */
        if(config->tftp_blksize)
          my_setopt(curl, CURLOPT_TFTP_BLKSIZE, config->tftp_blksize);

        if(config->mail_from)
          my_setopt_str(curl, CURLOPT_MAIL_FROM, config->mail_from);

        if(config->mail_rcpt)
          my_setopt_slist(curl, CURLOPT_MAIL_RCPT, config->mail_rcpt);

        /* curl 7.20.x */
        if(config->ftp_pret)
          my_setopt(curl, CURLOPT_FTP_USE_PRET, TRUE);

        if(config->proto_present)
          my_setopt_flags(curl, CURLOPT_PROTOCOLS, config->proto);
        if(config->proto_redir_present)
          my_setopt_flags(curl, CURLOPT_REDIR_PROTOCOLS, config->proto_redir);

        if((urlnode->flags & GETOUT_USEREMOTE)
           && config->content_disposition) {
          my_setopt(curl, CURLOPT_HEADERFUNCTION, tool_header_cb);
          my_setopt(curl, CURLOPT_HEADERDATA, &outs);
        }
