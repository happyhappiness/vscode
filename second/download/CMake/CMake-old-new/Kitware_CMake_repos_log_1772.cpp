(void)snprintf(tmp, sizeof(tmp), "%d.%d.%d.%d",
                 ((int)((unsigned char)src[0])) & 0xff,
                 ((int)((unsigned char)src[1])) & 0xff,
                 ((int)((unsigned char)src[2])) & 0xff,
                 ((int)((unsigned char)src[3])) & 0xff);