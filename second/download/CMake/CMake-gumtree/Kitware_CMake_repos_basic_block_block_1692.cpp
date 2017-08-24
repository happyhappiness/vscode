{
    // Calculate load since last time.
    load = 1.0 - double(idleTicksSinceLastTime) / totalTicksSinceLastTime;

    // Smooth if possible.
    if (previousLoad > 0) {
      load = 0.25 * load + 0.75 * previousLoad;
    }
  }