      size_t max_reduce = total_size;
      for (int i = 0; i < nlink; ++i) {
        if (i != parent_index) {
          max_reduce = std::min(max_reduce, links[i].size_read);
          utils::Assert(buffer_size == 0 || buffer_size == links[i].buffer_size,
                        "buffer size inconsistent");
          buffer_size = links[i].buffer_size;
