{
              new_bp = Address_Of_Nth_Buffer(field,i);
              old_bp = oldbuf + i*(1+old_buflen);
              memcpy(new_bp,old_bp,(size_t)old_buflen);
              if (new_buflen > old_buflen)
                memset(new_bp + old_buflen,C_BLANK,
                       (size_t)(new_buflen - old_buflen));
              *(new_bp + new_buflen) = '\0';
            }