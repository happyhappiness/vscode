CURLcode get_libcurl_info(void)
{
  static struct proto_name_pattern {
    const char *proto_name;
    long        proto_pattern;
  } const possibly_built_in[] = {
    { "dict",   CURLPROTO_DICT   },
    { "file",   CURLPROTO_FILE   },
    { "ftp",    CURLPROTO_FTP    },
    { "ftps",   CURLPROTO_FTPS   },
    { "gopher", CURLPROTO_GOPHER },
    { "http",   CURLPROTO_HTTP   },
    { "https",  CURLPROTO_HTTPS  },
    { "imap",   CURLPROTO_IMAP   },
    { "imaps",  CURLPROTO_IMAPS  },
    { "ldap",   CURLPROTO_LDAP   },
    { "ldaps",  CURLPROTO_LDAPS  },
    { "pop3",   CURLPROTO_POP3   },
    { "pop3s",  CURLPROTO_POP3S  },
    { "rtmp",   CURLPROTO_RTMP   },
    { "rtsp",   CURLPROTO_RTSP   },
    { "scp",    CURLPROTO_SCP    },
    { "sftp",   CURLPROTO_SFTP   },
    { "smb",    CURLPROTO_SMB    },
    { "smbs",   CURLPROTO_SMBS   },
    { "smtp",   CURLPROTO_SMTP   },
    { "smtps",  CURLPROTO_SMTPS  },
    { "telnet", CURLPROTO_TELNET },
    { "tftp",   CURLPROTO_TFTP   },
    {  NULL,    0                }
  };

  struct proto_name_pattern const *p;
  const char *const *proto;

  /* Pointer to libcurl's run-time version information */
  curlinfo = curl_version_info(CURLVERSION_NOW);
  if(!curlinfo)
    return CURLE_FAILED_INIT;

  /* Build CURLPROTO_* bit pattern with libcurl's built-in protocols */
  built_in_protos = 0;
  if(curlinfo->protocols) {
    for(proto = curlinfo->protocols; *proto; proto++) {
      for(p = possibly_built_in; p->proto_name; p++) {
        if(curlx_raw_equal(*proto, p->proto_name)) {
          built_in_protos |= p->proto_pattern;
          break;
        }
      }
    }
  }

  return CURLE_OK;
}