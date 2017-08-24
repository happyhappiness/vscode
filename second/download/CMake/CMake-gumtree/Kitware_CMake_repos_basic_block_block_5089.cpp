f(month >= 12) {
    year -= month / 12;
    month = month % 12;
  }