void customrequest_helper(struct OperationConfig *config, HttpReq req,
                          char *method)
{
  /* this mirrors the HttpReq enum in tool_sdecls.h */
  const char *dflt[]= {
    "GET",
    "GET",
    "HEAD",
    "POST",
    "POST"
  };

  if(!method)
    ;
  else if(curl_strequal(method, dflt[req])) {
    notef(config->global, "Unnecessary use of -X or --request, %s is already "
          "inferred.\n", dflt[req]);
  }
  else if(curl_strequal(method, "head")) {
    warnf(config->global,
          "Setting custom HTTP method to HEAD with -X/--request may not work "
          "the way you want. Consider using -I/--head instead.\n");
  }
}