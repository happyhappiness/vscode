(!((req->fs.info.mode & ~current_umask) & _S_IWRITE)) {
      attributes |= FILE_ATTRIBUTE_READONLY;
    }