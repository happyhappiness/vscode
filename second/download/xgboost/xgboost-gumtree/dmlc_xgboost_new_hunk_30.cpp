      tmp_ch = reader_.GetChar();
    }
    if (kStrictCheck) {
      CHECK_EQ(tlen, 0) << "Base64InStream: read incomplete";
    }
    return size - tlen;
  }
  virtual void Write(const void *ptr, size_t size) {
    LOG(FATAL) << "Base64InStream do not support write";
  }

 private:
