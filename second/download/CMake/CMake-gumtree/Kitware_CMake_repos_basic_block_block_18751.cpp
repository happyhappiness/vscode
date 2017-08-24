(err) {
      uv__close(peerfd);
      return err;
    }