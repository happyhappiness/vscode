{
      i64Total += GetCyclesDifference(SystemInformationImplementation::Delay,
                                      uiMSecPerRepetition);
      i64Overhead += GetCyclesDifference(
        SystemInformationImplementation::DelayOverhead, uiMSecPerRepetition);
    }