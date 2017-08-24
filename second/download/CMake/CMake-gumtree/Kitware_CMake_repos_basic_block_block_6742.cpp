{
    infof(data, "warning: certificate file name \"%s\" handled as nickname; "
          "please use \"./%s\" to force file name\n", str, str);
    return strdup(str);
  }