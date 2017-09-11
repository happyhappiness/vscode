CHECK_LT(sketch->temp.size, max_size)
                << "invalid maximum size max_size=" << max_size
                << ", stemp.size" << sketch->temp.size;