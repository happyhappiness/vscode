return snprintf(buffer, size, "mbedTLS/%d.%d.%d", version>>24,
                  (version>>16)&0xff, (version>>8)&0xff);