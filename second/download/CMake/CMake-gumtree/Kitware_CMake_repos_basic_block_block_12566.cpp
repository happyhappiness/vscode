((val = read_next_symbol(a, &precode)) < 0) {
        free(precode.tree);
        free(precode.table);
        return (ARCHIVE_FATAL);
      }