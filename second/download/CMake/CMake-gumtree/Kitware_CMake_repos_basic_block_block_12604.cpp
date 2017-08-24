(code->tree[lastnode].branches[bit] < 0)
      {
        if (new_node(code) < 0) {
          archive_set_error(&a->archive, ENOMEM,
                            "Unable to allocate memory for node data.");
          return (ARCHIVE_FATAL);
        }
        code->tree[lastnode].branches[bit] = code->numentries++;
      }