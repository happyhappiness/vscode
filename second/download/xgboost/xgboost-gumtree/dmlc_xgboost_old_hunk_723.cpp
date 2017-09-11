    namespace utils{
        inline void Error(const char *msg){
            fprintf(stderr, "Error:%s\n", msg);
            exit(-1);
        }

