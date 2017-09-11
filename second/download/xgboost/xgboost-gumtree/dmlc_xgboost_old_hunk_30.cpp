      tmp_ch = reader_.GetChar();
    }
    if (kStrictCheck) {
      utils::Check(tlen == 0, "Base64InStream: read incomplete");
    }
    return size - tlen;
  }
  virtual void Write(const void *ptr, size_t size) {
    utils::Error("Base64InStream do not support write");
  }

 private:
