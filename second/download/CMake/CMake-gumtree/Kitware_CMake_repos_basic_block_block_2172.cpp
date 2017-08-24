{
    /* To support the full 64-bit file size, use fs.nFileSizeHigh
     * and fs.nFileSizeLow to construct the 64 bit size

    length = ((__int64)fs.nFileSizeHigh << 32) + fs.nFileSizeLow;
     */
    length = static_cast<unsigned long>(fs.nFileSizeLow);
  }