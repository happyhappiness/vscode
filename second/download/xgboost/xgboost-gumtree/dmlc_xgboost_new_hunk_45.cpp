        ++dst; ++b;
      } while (b != b_end);
    }
    CHECK(dst == data + size) << "bug in combine";
  }
};

