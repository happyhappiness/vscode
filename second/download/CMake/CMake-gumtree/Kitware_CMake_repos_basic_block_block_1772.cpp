(this->ChipID.Family == 4) {
    // 80486 processors....  Loop time is 47 cycles!
    dFrequency = (((CLASSICAL_CPU_FREQ_LOOP * 47) / dDifference) / 1000000);
  }