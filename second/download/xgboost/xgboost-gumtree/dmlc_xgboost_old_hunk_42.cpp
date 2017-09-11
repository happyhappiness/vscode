    }
    if (nbig >= n - 1) {
      // see what was the case
      utils::Printf("LOG: check quantile stats, nbig=%lu, n=%lu\n", nbig, n);
      utils::Printf("LOG: srcsize=%lu, maxsize=%lu, range=%g, chunk=%g\n",
                    src.size, maxsize, static_cast<double>(range),
                    static_cast<double>(chunk));
      src.Print();
      utils::Assert(nbig < n - 1, "quantile: too many large chunk");
    }
    this->data[0] = src.data[0];
    this->size = 1;
