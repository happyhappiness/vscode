    if (sb.size == 0) {
      this->CopyFrom(sa); return;
    }
    CHECK(sa.size > 0 && sb.size > 0);
    const Entry *a = sa.data, *a_end = sa.data + sa.size;
    const Entry *b = sb.data, *b_end = sb.data + sb.size;
    // extended rmin value
