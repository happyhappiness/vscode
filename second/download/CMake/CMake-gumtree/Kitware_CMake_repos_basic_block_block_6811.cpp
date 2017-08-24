{
  case CURLE_OK:
    infof(data, "pinned public key verified successfully!\n");
    break;
  case CURLE_SSL_PINNEDPUBKEYNOTMATCH:
    failf(data, "failed to verify pinned public key");
    break;
  default:
    /* OOM, etc. */
    break;
  }