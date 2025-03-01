int main(int argc, char ** argv) {


void * libptr;
const char * (*ssl_version)(int t);
const char * version;

   if (argc < 1) {
       puts("report_openssl_version filename");
       exit(1);
   }

   libptr = dlopen(argv[1], 0);

   ssl_version = (const char * (*)(int))dlsym(libptr, "SSLeay_version");
   if ((void *)ssl_version == NULL) {
      ssl_version = (const char * (*)(int))dlsym(libptr, "ssleay_version");
      if ((void *)ssl_version == NULL) {
         ssl_version = (const char * (*)(int))dlsym(libptr, "SSLEAY_VERSION");
      }
   }

   dlclose(libptr);

   if ((void *)ssl_version == NULL) {
      puts("Unable to lookup version of OpenSSL");
      exit(1);
   }

   version = ssl_version(SSLEAY_VERSION);

   puts(version);

   /* Was a symbol argument given? */
   if (argc > 1) {
      int status;
      struct dsc$descriptor_s symbol_dsc;
      struct dsc$descriptor_s value_dsc;
      const unsigned long table_type = LIB$K_CLI_LOCAL_SYM;

      symbol_dsc.dsc$a_pointer = argv[2];
      symbol_dsc.dsc$w_length = strlen(argv[2]);
      symbol_dsc.dsc$b_dtype = DSC$K_DTYPE_T;
      symbol_dsc.dsc$b_class = DSC$K_CLASS_S;

      value_dsc.dsc$a_pointer = (char *)version; /* Cast ok */
      value_dsc.dsc$w_length = strlen(version);
      value_dsc.dsc$b_dtype = DSC$K_DTYPE_T;
      value_dsc.dsc$b_class = DSC$K_CLASS_S;

      status = LIB$SET_SYMBOL(&symbol_dsc, &value_dsc, &table_type);
      if (!$VMS_STATUS_SUCCESS(status)) {
         exit(status);
      }
   }

   exit(0);
}