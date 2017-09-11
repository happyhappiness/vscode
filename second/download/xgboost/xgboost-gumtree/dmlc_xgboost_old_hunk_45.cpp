        ++dst; ++b;
      } while (b != b_end);
    }
    utils::Assert(dst == data + size, "bug in combine");
  }
};

