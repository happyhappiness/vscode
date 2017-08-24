{
  case 2:
    if(!strncasecompare("te", name, namelen))
      return HEADERINST_FORWARD;

    return contains_trailers(value, valuelen) ?
           HEADERINST_TE_TRAILERS : HEADERINST_IGNORE;
  case 7:
    return strncasecompare("upgrade", name, namelen) ?
           HEADERINST_IGNORE : HEADERINST_FORWARD;
  case 10:
    return (strncasecompare("connection", name, namelen) ||
            strncasecompare("keep-alive", name, namelen)) ?
           HEADERINST_IGNORE : HEADERINST_FORWARD;
  case 16:
    return strncasecompare("proxy-connection", name, namelen) ?
           HEADERINST_IGNORE : HEADERINST_FORWARD;
  case 17:
    return strncasecompare("transfer-encoding", name, namelen) ?
           HEADERINST_IGNORE : HEADERINST_FORWARD;
  default:
    return HEADERINST_FORWARD;
  }