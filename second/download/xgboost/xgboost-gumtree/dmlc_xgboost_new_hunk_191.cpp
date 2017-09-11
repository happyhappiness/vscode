      utils::Printf("LOG: srcsize=%lu, maxsize=%lu, range=%g, chunk=%g\n",
                    src.size, maxsize, static_cast<double>(range),
                    static_cast<double>(chunk));
      src.Print();
      utils::Assert(nbig < n - 1, "quantile: too many large chunk");
    }
    this->data[0] = src.data[0];
