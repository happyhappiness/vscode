(EQ(obj, dev) || EQ(uv__rawname(obj), dev) || EQ(stub, dev)) {
      uv__free(p);  /* Found a match */
      return 0;
    }