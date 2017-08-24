(r != ARCHIVE_OK) {
      free(precode.tree);
      free(precode.table);
      return (r);
    }