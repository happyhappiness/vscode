  case PARAM_BAD_NUMERIC:
    return "expected a proper numerical parameter";
  case PARAM_NEGATIVE_NUMERIC:
    return "expected a positive numerical parameter";
  case PARAM_LIBCURL_DOESNT_SUPPORT:
    return "the installed libcurl version doesn't support this";
  case PARAM_NO_MEM:
    return "out of memory";
  default:
    return "unknown error";
  }
}

int SetHTTPrequest(struct OperationConfig *config, HttpReq req, HttpReq *store)
{
  if((*store == HTTPREQ_UNSPEC) ||
     (*store == req)) {
    *store = req;
    return 0;
  }

  warnf(config->global, "You can only select one HTTP request!\n");

  return 1;
}
