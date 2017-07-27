return snprintf(buffer, size, "%s/%d.%d.%d",
                  version >= 0x01030A00?"mbedTLS":"PolarSSL",
                  version>>24, (version>>16)&0xff, (version>>8)&0xff);