        mrange += src.data[src.size-1].rmax_prev() - src.data[bid].rmin_next();
      }
    }
    utils::Assert(nbig < n - 1, "too many large chunk");
    this->data[0] = src.data[0];
    this->size = 1;
    // use smaller size
