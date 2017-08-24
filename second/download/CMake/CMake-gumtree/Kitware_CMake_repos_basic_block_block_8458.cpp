(unsigned index = 0; index < size; ++index) {
        if (index > 0)
          document_ += ", ";
        document_ += childValues_[index];
      }