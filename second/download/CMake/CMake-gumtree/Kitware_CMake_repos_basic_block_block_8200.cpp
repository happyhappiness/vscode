(iter->p != iter->end) {
    NAMED *tem = *(iter->p)++;
    if (tem)
      return tem;
  }