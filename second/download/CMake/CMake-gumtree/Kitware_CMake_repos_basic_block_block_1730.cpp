((SupportsSMT) && (this->Features.HasAPIC)) {
      // Retrieve APIC information if there is one present.
      this->Features.ExtendedFeatures.APIC_ID =
        ((cpuinfo[1] & 0xFF000000) >> 24);
    }