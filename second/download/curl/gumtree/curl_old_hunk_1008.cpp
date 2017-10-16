  else if(curl_strequal(method, dflt[req])) {
    notef(config->global, "Unnecessary use of -X or --request, %s is already "
          "inferred.\n", dflt[req]);
  }
  else if(curl_strequal(method, "head")) {
    warnf(config->global,
          "Setting custom HTTP method to HEAD may not work the way you "
          "want.\n");
  }
}
