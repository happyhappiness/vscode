(!rar->br.next_in &&
      (ret = rar_br_preparation(a, &(rar->br))) < ARCHIVE_WARN)
      return (ret);