(c[0] == '~') {
    // Home directory.  The returned root should always have a
    // trailing slash so that appending components as
    // c[0]c[1]/c[2]/... works.  The remaining path returned should
    // skip the first slash if it exists:
    //
    //   "~"    : root = "~/" , return ""
    //   "~/    : root = "~/" , return ""
    //   "~/x   : root = "~/" , return "x"
    //   "~u"   : root = "~u/", return ""
    //   "~u/"  : root = "~u/", return ""
    //   "~u/x" : root = "~u/", return "x"
    size_t n = 1;
    while (c[n] && c[n] != '/') {
      ++n;
    }
    if (root) {
      root->assign(c, n);
      *root += '/';
    }
    if (c[n] == '/') {
      ++n;
    }
    c += n;
  }