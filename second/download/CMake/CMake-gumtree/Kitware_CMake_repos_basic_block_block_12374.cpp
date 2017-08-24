{
    case 8:
      if (br->avail_in >= 8) {
        br->cache_buffer =
            ((uint64_t)br->next_in[0]) << 56 |
            ((uint64_t)br->next_in[1]) << 48 |
            ((uint64_t)br->next_in[2]) << 40 |
            ((uint64_t)br->next_in[3]) << 32 |
            ((uint32_t)br->next_in[4]) << 24 |
            ((uint32_t)br->next_in[5]) << 16 |
            ((uint32_t)br->next_in[6]) << 8 |
             (uint32_t)br->next_in[7];
        br->next_in += 8;
        br->avail_in -= 8;
        br->cache_avail += 8 * 8;
        rar->bytes_unconsumed += 8;
        rar->bytes_remaining -= 8;
        return (1);
      }
      break;
    case 7:
      if (br->avail_in >= 7) {
        br->cache_buffer =
           (br->cache_buffer << 56) |
            ((uint64_t)br->next_in[0]) << 48 |
            ((uint64_t)br->next_in[1]) << 40 |
            ((uint64_t)br->next_in[2]) << 32 |
            ((uint32_t)br->next_in[3]) << 24 |
            ((uint32_t)br->next_in[4]) << 16 |
            ((uint32_t)br->next_in[5]) << 8 |
             (uint32_t)br->next_in[6];
        br->next_in += 7;
        br->avail_in -= 7;
        br->cache_avail += 7 * 8;
        rar->bytes_unconsumed += 7;
        rar->bytes_remaining -= 7;
        return (1);
      }
      break;
    case 6:
      if (br->avail_in >= 6) {
        br->cache_buffer =
           (br->cache_buffer << 48) |
            ((uint64_t)br->next_in[0]) << 40 |
            ((uint64_t)br->next_in[1]) << 32 |
            ((uint32_t)br->next_in[2]) << 24 |
            ((uint32_t)br->next_in[3]) << 16 |
            ((uint32_t)br->next_in[4]) << 8 |
             (uint32_t)br->next_in[5];
        br->next_in += 6;
        br->avail_in -= 6;
        br->cache_avail += 6 * 8;
        rar->bytes_unconsumed += 6;
        rar->bytes_remaining -= 6;
        return (1);
      }
      break;
    case 0:
      /* We have enough compressed data in
       * the cache buffer.*/
      return (1);
    default:
      break;
    }