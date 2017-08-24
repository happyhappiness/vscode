{
      ret |= make_table_recurse(a, code, code->tree[node].branches[0], table,
                                depth + 1, maxdepth);
      ret |= make_table_recurse(a, code, code->tree[node].branches[1],
                         table + currtablesize / 2, depth + 1, maxdepth);
    }