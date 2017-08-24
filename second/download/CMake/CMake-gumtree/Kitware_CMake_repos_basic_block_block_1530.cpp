(ind-- != 0)                            // Else while still characters
    if (this->program[ind] != rxp.program[ind]) // If regexp are different
      return false;