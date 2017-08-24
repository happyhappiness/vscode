f((fp_w = fopen(fn_w,"wb"))==NULL){
               printf("can't open [%s]\n",fn_w);
               perror("reason:");
               exit(1);
            }