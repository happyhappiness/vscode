{
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION PInfo = *it;
    if (PInfo.Relationship != RelationProcessorCore) {
      continue;
    }

    std::bitset<std::numeric_limits<ULONG_PTR>::digits> ProcMask(
      (unsigned long long)PInfo.ProcessorMask);
    unsigned int count = (unsigned int)ProcMask.count();
    if (count == 0) { // I think this should never happen, but just to be safe.
      continue;
    }
    this->NumberOfPhysicalCPU++;
    this->NumberOfLogicalCPU += (unsigned int)count;
    this->Features.ExtendedFeatures.LogicalProcessorsPerPhysical = count;
  }