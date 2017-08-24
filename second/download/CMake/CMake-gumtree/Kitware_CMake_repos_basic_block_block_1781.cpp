(this->ChipManufacturer == Transmeta) {
    if (this->ChipID.Family < 5)
      return false;
  }