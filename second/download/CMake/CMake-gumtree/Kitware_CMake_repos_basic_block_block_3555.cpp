e{
         BZFILE *BZ2fp_w = NULL;
         FILE *fp_r = NULL;

         if(fn_r){
            if((fp_r = fopen(fn_r,"rb"))==NULL){
               printf("can't open [%s]\n",fn_r);
               perror("reason:");
               exit(1);
            }
         }else{
            fp_r = stdin;
         }
         mode[0]='w';
         mode[1] = '0' + level;
         mode[2] = '\0';

         if((fn_w == NULL && (BZ2fp_w = BZ2_bzdopen(fileno(stdout),mode))==NULL)
            || (fn_w !=NULL && (BZ2fp_w = BZ2_bzopen(fn_w,mode))==NULL)){
            printf("can't bz2openstream\n");
            exit(1);
         }
         while((len=fread(buff,1,0x1000,fp_r))>0){
            BZ2_bzwrite(BZ2fp_w,buff,len);
         }
         BZ2_bzclose(BZ2fp_w);
         if(fp_r!=stdin)fclose(fp_r);
      }