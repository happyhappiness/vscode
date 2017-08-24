(strlen(environ[in]) > len && environ[in][len] == '=' &&
        strncmp(env.c_str(), environ[in], len) == 0) {
      ++in;
    } else {
      environ[out++] = environ[in++];
    }