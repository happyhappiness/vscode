utils::Assert(sketch->temp.size <= max_size,
                      "Finalize: invalid maximum size, max_size=%u, stemp.size=%lu",
                      sketch->temp.size, max_size);