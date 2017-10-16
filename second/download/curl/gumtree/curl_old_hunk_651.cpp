        break;
      case 'j': /* --ftp-ssl-ccc-mode */
        config->ftp_ssl_ccc = TRUE;
        config->ftp_ssl_ccc_mode = ftpcccmethod(config, nextarg);
        break;
      case 'z': /* --libcurl */
        GetStr(&config->libcurl, nextarg);
        break;
      case '#': /* --raw */
        config->raw = toggle;
        break;
      case '0': /* --post301 */
        config->post301 = toggle;
        break;
