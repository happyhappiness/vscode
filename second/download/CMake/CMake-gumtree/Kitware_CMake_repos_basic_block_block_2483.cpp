{
    std::cerr << std::setbase(16) << std::setfill('0') << "     "
              << "0x" << std::setw(8) << static_cast<unsigned int>(expected[i])
              << " | "
              << "0x" << std::setw(8)
              << static_cast<unsigned int>(received[i]);
    if (static_cast<unsigned int>(expected[i]) !=
        static_cast<unsigned int>(received[i])) {
      std::cerr << "   MISMATCH!";
    }
    std::cerr << std::endl;
  }