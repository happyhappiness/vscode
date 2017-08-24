r(i = 0; i < 16 && data->change.url[i]; ++i) {
      if(data->change.url[i] == '/')
        break;
      if(data->change.url[i] == ':') {
        url_has_scheme = TRUE;
        break;
      }
    }