{
              unsigned cp = filename_size >> 1;
              filename[filename_size++] = high;
              filename[filename_size++] = p[cp] + extra;
              length--;
            }