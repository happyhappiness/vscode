utils::Assert(sketch->temp.size < max_size,
                          "invalid maximum size max_size=%u, stemp.size=%lu\n",
                          max_size, sketch->temp.size);