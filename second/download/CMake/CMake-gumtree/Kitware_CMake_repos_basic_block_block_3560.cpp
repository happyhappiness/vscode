r(p=*argv+1;*p;p++){
            if(*p=='d'){
               decompress = 1;
            }else if('1'<=*p && *p<='9'){
               level = *p - '0';
            }else{
               usage();
               exit(1);
            }
         }