    }
    if (nbig >= n - 1) {
      // see what was the case
      LOG(INFO) << " check quantile stats, nbig=" << nbig << ", n=" << n;
      LOG(INFO) << " srcsize=" << src.size << ", maxsize=" << maxsize
                << ", range=" << range << ", chunk=" << chunk;
      src.Print();
      CHECK(nbig < n - 1) << "quantile: too many large chunk";
    }
    this->data[0] = src.data[0];
    this->size = 1;
