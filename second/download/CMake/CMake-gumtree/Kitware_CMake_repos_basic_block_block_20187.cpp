(!CryptGenRandom(h_crypt_prov, sizeof(v), (BYTE*) &v)) {
      SET_REQ_WIN32_ERROR(req, GetLastError());
      break;
    }