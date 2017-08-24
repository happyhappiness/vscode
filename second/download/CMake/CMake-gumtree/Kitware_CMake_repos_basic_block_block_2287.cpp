{
      // End of a component.  Save it.
      components.push_back(std::string(first, last));
      first = last + 1;
    }