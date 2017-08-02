{
    fprintf(stderr, "Entropy: %s --> 0x%0*lx (%lu bytes)\n",
        label,
        (int)sizeof(entropy) * 2, entropy,
        (unsigned long)sizeof(entropy));
  }