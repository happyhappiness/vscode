{         // Same address?
    int ind = this->progsize; // Get regular expression size
    if (ind != rxp.progsize)  // If different size regexp
      return false;           // Return failure
    while (ind-- != 0)        // Else while still characters
      if (this->program[ind] != rxp.program[ind]) // If regexp are different
        return false;                             // Return failure
  }