{
      /* Open branch check */
      if (!(code->tree[lastnode].branches[bit] < 0))
      {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "Invalid repeating code");
        return (ARCHIVE_FATAL);
      }

      if ((repeatnode = new_node(code)) < 0) {
        archive_set_error(&a->archive, ENOMEM,
                          "Unable to allocate memory for node data.");
        return (ARCHIVE_FATAL);
      }
      if ((nextnode = new_node(code)) < 0) {
        archive_set_error(&a->archive, ENOMEM,
                          "Unable to allocate memory for node data.");
        return (ARCHIVE_FATAL);
      }

      /* Set branches */
      code->tree[lastnode].branches[bit] = repeatnode;
      code->tree[repeatnode].branches[bit] = repeatnode;
      code->tree[repeatnode].branches[bit^1] = nextnode;
      lastnode = nextnode;

      bitpos++; /* terminating bit already handled, skip it */
    }