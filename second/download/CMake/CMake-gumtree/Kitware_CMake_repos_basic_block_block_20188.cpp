do {
    if (!CryptGenRandom(h_crypt_prov, sizeof(v), (BYTE*) &v)) {
      SET_REQ_WIN32_ERROR(req, GetLastError());
      break;
    }

    cp = ep - num_x;
    for (i = 0; i < num_x; i++) {
      *cp++ = tempchars[v % num_chars];
      v /= num_chars;
    }

    if (_wmkdir(req->file.pathw) == 0) {
      len = strlen(req->path);
      wcstombs((char*) req->path + len - num_x, ep - num_x, num_x);
      SET_REQ_RESULT(req, 0);
      break;
    } else if (errno != EEXIST) {
      SET_REQ_RESULT(req, -1);
      break;
    }
  } while (--tries);