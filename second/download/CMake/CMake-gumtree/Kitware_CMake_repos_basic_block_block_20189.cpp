(errno != EEXIST) {
      SET_REQ_RESULT(req, -1);
      break;
    }