do {
    // Get the ending position of the counter.
    QueryPerformanceCounter(&EndCounter);
  } while (EndCounter.QuadPart - StartCounter.QuadPart == x);