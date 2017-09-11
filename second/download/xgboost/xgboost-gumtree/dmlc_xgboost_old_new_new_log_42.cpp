CHECK_LE(sketch->temp.size, max_size)
            << "Finalize: invalid maximum size, max_size=" << max_size
            << ", stemp.size=" << sketch->temp.size;