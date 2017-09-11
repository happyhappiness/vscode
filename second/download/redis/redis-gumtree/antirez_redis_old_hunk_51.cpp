    fflush(stdout);
}

#ifdef BENCHMARK_MAIN
#include <stdio.h>
#include <sys/time.h>

/* This is a simple Feistel network in order to turn every possible
 * uint32_t input into another "randomly" looking uint32_t. It is a
 * one to one map so there are no repetitions. */
static uint32_t int2int(uint32_t input) {
    uint16_t l = input & 0xffff;
    uint16_t r = input >> 16;
    for (int i = 0; i < 8; i++) {
        uint16_t nl = r;
        uint16_t F = (((r * 31) + (r >> 5) + 7 * 371) ^ r) & 0xffff;
        r = l ^ F;
        l = nl;
    }
    return (r<<16)|l;
}

/* Turn an uint32_t integer into an alphanumerical key and return its
 * length. This function is used in order to generate keys that have
 * a large charset, so that the radix tree can be testsed with many
 * children per node. */
static size_t int2alphakey(char *s, size_t maxlen, uint32_t i) {
    const char *set = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "abcdefghijklmnopqrstuvwxyz"
                      "0123456789";
    const size_t setlen = 62;

    if (maxlen == 0) return 0;
    maxlen--; /* Space for null term char. */
    size_t len = 0;
    while(len < maxlen) {
        s[len++] = set[i%setlen];
        i /= setlen;
        if (i == 0) break;
    }
    s[len] = '\0';
    return len;
}

/* Return the UNIX time in microseconds */
static long long ustime(void) {
    struct timeval tv;
    long long ust;

    gettimeofday(&tv, NULL);
    ust = ((long long)tv.tv_sec)*1000000;
    ust += tv.tv_usec;
    return ust;
}

/* Turn the integer 'i' into a key according to 'mode'.
 * mode = 0, just represents the integer as a string.
 * mode = 1, turn it into a random-looking alphanumerical string
 *           according to the int2alphakey() function. */
static size_t int2key(char *s, size_t maxlen, uint32_t i, int mode) {
    if (mode == 0) {
        return snprintf(s,maxlen,"%lu",(unsigned long)i);
    } else {
        i = int2int(i);
        return int2alphakey(s,maxlen,i);
    }
}

int main(void) {
    for (int mode = 0; mode < 2; mode++) {
        printf("Benchmark with %s keys:\n",
            (mode == 0) ? "integer" : "alphanumerical");
        rax *t = raxNew();
        long long start = ustime();
        for (int i = 0; i < 5000000; i++) {
            char buf[64];
            int len = int2key(buf,sizeof(buf),i,mode);
            raxInsert(t,(unsigned char*)buf,len,(void*)(long)i);
        }
        printf("Insert: %f\n", (double)(ustime()-start)/1000000);
        printf("%llu total nodes\n", (unsigned long long)t->numnodes);
        printf("%llu total elements\n", (unsigned long long)t->numele);

        start = ustime();
        for (int i = 0; i < 5000000; i++) {
            char buf[64];
            int len = int2key(buf,sizeof(buf),i,mode);
            void *data = raxFind(t,(unsigned char*)buf,len);
            if (data != (void*)(long)i) {
                printf("Issue with %s: %p instead of %p\n", buf,
                    data, (void*)(long)i);
            }
        }
        printf("Lookup: %f\n", (double)(ustime()-start)/1000000);

        start = ustime();
        for (int i = 0; i < 5000000; i++) {
            char buf[64];
            int r = rand() % 5000000;
            int len = int2key(buf,sizeof(buf),r,mode);
            void *data = raxFind(t,(unsigned char*)buf,len);
            if (data != (void*)(long)r) {
                printf("Issue with %s: %p instead of %p\n", buf,
                    data, (void*)(long)r);
            }
        }
        printf("Random lookup: %f\n", (double)(ustime()-start)/1000000);

        start = ustime();
        int count = 0;
        for (int i = 0; i < 5000000; i++) {
            char buf[64];
            int len = int2key(buf,sizeof(buf),i,mode);
            buf[i%len] = '!'; /* "!" is never set into keys. */
            void *data = raxFind(t,(unsigned char*) buf,len);
            if (data != (void*)(long)i) count++;
        }
        printf("Failed lookup: %f\n", (double)(ustime()-start)/1000000);

        start = ustime();
        for (int i = 0; i < 5000000; i++) {
            char buf[64];
            int len = int2key(buf,sizeof(buf),i,mode);
            int retval = raxRemove(t,(unsigned char*)buf,len);
            assert(retval == 1);
        }
        printf("Deletion: %f\n", (double)(ustime()-start)/1000000);

        printf("%llu total nodes\n", (unsigned long long)t->numnodes);
        printf("%llu total elements\n", (unsigned long long)t->numele);
        raxFree(t);
    }
    return 0;
}
#endif

#ifdef TEST_MAIN
#include <stdio.h>
#include <time.h>

int main(void) {
    printf("notfound = %p\n", raxNotFound);
    rax *t = raxNew();
    char *toadd[] = {"alligator","alien","baloon","chromodynamic","romane","romanus","romulus","rubens","ruber","rubicon","rubicundus","all","rub","ba",NULL};

    srand(time(NULL));
    for (int x = 0; x < 10000; x++) rand();

    long items = 0;
    while(toadd[items] != NULL) items++;

    for (long i = 0; i < items; i++) {
        raxInsert(t,(unsigned char*)toadd[i],strlen(toadd[i]),(void*)i);
        printf("Added %s\n", toadd[i]);
    }
    raxShow(t);

    raxIterator iter;
    raxStart(&iter,t);

    // OK: all this tests will need to go in the Rax unit test.
    // raxSeek(&iter,(unsigned char*)"rpxxx",5,"<=");
    // raxSeek(&iter,(unsigned char*)"rom",3,">=");
    // raxSeek(&iter,(unsigned char*)"rub",3,">=");
    // raxSeek(&iter,(unsigned char*)"rub",3,">");
    // raxSeek(&iter,(unsigned char*)"rub",3,"<");
    // raxSeek(&iter,(unsigned char*)"rom",3,">");
    // raxSeek(&iter,(unsigned char*)"chro",4,">");
    // raxSeek(&iter,(unsigned char*)"chro",4,"<");
    // raxSeek(&iter,(unsigned char*)"chromz",6,"<");
    // raxSeek(&iter,NULL,0,"^");
    // raxSeek(&iter,"zorro",5,"<=");
    // raxSeek(&iter,"zorro",5,"<");
    // raxSeek(&iter,NULL,0,"$");

    // STILL TO TEST
    raxSeek(&iter,(unsigned char*)"ro",2,">=");
    printf("EOF: %d\n", (iter.flags & RAX_ITER_EOF) != 0);

    printf("SEEKED: %.*s, val %p\n", (int)iter.key_len,
                                     (char*)iter.key,
                                     iter.data);

    printf("NEXT\n");
    while(raxNext(&iter,NULL,0,NULL)) {
        printf("--- key: %.*s, val %p\n", (int)iter.key_len,
                                      (char*)iter.key,
                                      iter.data);
    }

    printf("After EOF element is: %.*s\n", (int)iter.key_len,
                                      (char*)iter.key);
    printf("~~~~~~~~~~~~~~\n");

    printf("PREV\n");
    raxSeek(&iter,iter.key,iter.key_len,"==");
    while(raxPrev(&iter,NULL,0,NULL)) {
        printf("--- key: %.*s, val %p\n", (int)iter.key_len,
                                      (char*)iter.key,
                                      iter.data);
    }

    printf("After EOF element is: %.*s\n", (int)iter.key_len,
                                      (char*)iter.key);
    raxStop(&iter);

#if 0
    raxStop(&iter);
#endif
    exit(0);

    int rnum = rand();
    int survivor = rnum % items;

#if 1
    printf("Removing everything but %s in random order\n", toadd[survivor]);
    for (long i = 0; i < 1000; i++) {
        int r = rand() % items;
        if (r == survivor) continue;
        raxRemove(t,(unsigned char*)toadd[r],strlen(toadd[r]));
    }
#else
    printf("Removing rubicon\n");
    raxRemove(t,(unsigned char*)"rubicon",7);
#endif

    printf("%llu total nodes\n", (unsigned long long)t->numnodes);
    printf("%llu total elements\n", (unsigned long long)t->numele);

    raxShow(t);
    raxFree(t);
}
#endif
