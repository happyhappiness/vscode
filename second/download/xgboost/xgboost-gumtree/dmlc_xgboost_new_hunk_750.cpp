    namespace utils{
        inline void Error(const char *msg){
            fprintf(stderr, "Error:%s\n", msg);
            fflush(stderr);
            exit(-1);
        }

