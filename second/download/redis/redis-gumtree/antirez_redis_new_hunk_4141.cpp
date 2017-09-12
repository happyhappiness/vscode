            o->encoding = REDIS_ENCODING_INT;
            o->ptr = (void*)((long)value);
        } else {
            char buf[32], *p;
            char *c = "0123456789";
            unsigned long v;

            v = (value < 0) ? -value : value;
            p = buf+31; /* point to the last character */
            while(v) {
                *p-- = c[v%10];
                v /= 10;
            }
            if (value < 0) *p-- = '-';
            p++;
            o = createObject(REDIS_STRING,sdsnewlen(p,32-(p-buf+1)));
        }
    }
    return o;
