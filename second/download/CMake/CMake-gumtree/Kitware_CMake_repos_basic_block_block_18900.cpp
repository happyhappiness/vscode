(req->nbufs == 1) {
      result = pread(req->file, req->bufs[0].base, req->bufs[0].len, req->off);
      goto done;
    }