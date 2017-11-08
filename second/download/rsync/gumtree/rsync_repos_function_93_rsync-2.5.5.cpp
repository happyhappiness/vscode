static int make_bak_dir(char *fname,char *bak_path)
{
        STRUCT_STAT st;
        STRUCT_STAT *st2;
        char fullpath[MAXPATHLEN];
        extern int orig_umask;
        char *p;
        char *q;

        while(strncmp(bak_path,"./",2)==0) bak_path += 2;

        if(bak_path[strlen(bak_path)-1]!='/') {
                snprintf(fullpath,sizeof(fullpath),"%s/",bak_path);
        } else {
                snprintf(fullpath,sizeof(fullpath),"%s",bak_path);
        }
        p=fullpath;
        q=&fullpath[strlen(fullpath)];  /* End of bak_path string */
        strcat(fullpath,fname);

        /* Make the directories */
        while ((p=strchr(p,'/'))) {
                *p = 0;
                if(do_lstat(fullpath,&st)!=0) {
                        do_mkdir(fullpath,0777 & ~orig_umask);
                        if(p>q) {
                                if(do_lstat(q,&st)!=0) {
                                        rprintf(FERROR,"make_bak_dir stat %s : %s\n",fullpath,strerror(errno));
                                } else {
                                        st2=&st;
                                        set_modtime(fullpath,st2->st_mtime);
                                        if(do_lchown(fullpath,st2->st_uid,st2->st_gid)!=0) {
                                                rprintf(FERROR,"make_bak_dir chown %s : %s\n",fullpath,strerror(errno));
                                        };
                                        if(do_chmod(fullpath,st2->st_mode)!=0) {
                                                rprintf(FERROR,"make_bak_dir failed to set permissions on %s : %s\n",fullpath,strerror(errno));
                                        };
                                };
                        }
                };
                *p = '/';
                p++;
        }
        return 0;
}