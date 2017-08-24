{
        tp += sizeof(struct in_addr);
        seen_xdigits = 0;
        break;  /*%< '\\0' was seen by inet_pton4(). */
      }