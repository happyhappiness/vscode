{
    for (unsigned int nCounter = 0; nCounter < uiRepetitions; nCounter++) {
      i64Total += GetCyclesDifference(SystemInformationImplementation::Delay,
                                      uiMSecPerRepetition);
      i64Overhead += GetCyclesDifference(
        SystemInformationImplementation::DelayOverhead, uiMSecPerRepetition);
    }

    // Calculate the MHz speed.
    i64Total -= i64Overhead;
    i64Total /= uiRepetitions;
    i64Total /= uiMSecPerRepetition;
    i64Total /= 1000;

    // Save the CPU speed.
    this->CPUSpeedInMHz = (float)i64Total;

    retrieved = true;
  }