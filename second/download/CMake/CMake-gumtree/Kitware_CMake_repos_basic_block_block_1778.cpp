(this->ChipManufacturer == Intel) {
    if (this->ChipID.Family < 0xf) {
      return false;
    }
  }