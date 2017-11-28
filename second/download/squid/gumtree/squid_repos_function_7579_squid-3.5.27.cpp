SMB_Tree_Handle SMB_TreeConnect(SMB_Handle_Type Con_Handle,
                                SMB_Tree_Handle Tree_Handle,
                                const char *path,
                                const char *password,
                                const char *device)

{
    struct RFCNB_Pkt *pkt;
    int param_len, pkt_len;
    char *p;
    SMB_Tree_Handle tree;

    /* Figure out how much space is needed for path, password, dev ... */

    if ((path == NULL) | (password == NULL) | (device == NULL)) {

#ifdef DEBUG
        fprintf(stderr, "Bad parameter passed to SMB_TreeConnect\n");
#endif

        SMBlib_errno = SMBlibE_BadParam;
        return(NULL);

    }

    /* The + 2 is because of the \0 and the marker ...                    */

    param_len = strlen(path) + 2 + strlen(password) + 2 + strlen(device) + 2;

    /* The -1 accounts for the one byte smb_buf we have because some systems */
    /* don't like char msg_buf[]                                             */

    pkt_len = SMB_tcon_len + param_len;

    pkt = (struct RFCNB_Pkt *)RFCNB_Alloc_Pkt(pkt_len);

    if (pkt == NULL) {

        SMBlib_errno = SMBlibE_NoSpace;
        return(NULL); /* Should handle the error */

    }

    /* Now allocate a tree for this to go into ... */

    if (Tree_Handle == NULL) {

        tree = (SMB_Tree_Handle)malloc(sizeof(struct SMB_Tree_Structure));

        if (tree == NULL) {

            RFCNB_Free_Pkt(pkt);
            SMBlib_errno = SMBlibE_NoSpace;
            return(NULL);

        }
    } else {

        tree = Tree_Handle;

    }

    tree -> next = tree -> prev = NULL;
    tree -> con = Con_Handle;
    strncpy(tree -> path, path, sizeof(tree -> path));
    strncpy(tree -> device_type, device, sizeof(tree -> device_type));

    /* Now plug in the values ... */

    memset(SMB_Hdr(pkt), 0, SMB_tcon_len);
    SIVAL(SMB_Hdr(pkt), SMB_hdr_idf_offset, SMB_DEF_IDF);  /* Plunk in IDF */
    *(SMB_Hdr(pkt) + SMB_hdr_com_offset) = SMBtcon;
    SSVAL(SMB_Hdr(pkt), SMB_hdr_pid_offset, Con_Handle -> pid);
    SSVAL(SMB_Hdr(pkt), SMB_hdr_tid_offset, 0);
    SSVAL(SMB_Hdr(pkt), SMB_hdr_mid_offset, Con_Handle -> mid);
    SSVAL(SMB_Hdr(pkt), SMB_hdr_uid_offset, Con_Handle -> uid);
    *(SMB_Hdr(pkt) + SMB_hdr_wct_offset) = 0;

    SSVAL(SMB_Hdr(pkt), SMB_tcon_bcc_offset, param_len);

    /* Now copy the param strings in with the right stuff */

    p = (char *)(SMB_Hdr(pkt) + SMB_tcon_buf_offset);
    *p = SMBasciiID;
    strcpy(p + 1, path);
    p = p + strlen(path) + 2;
    *p = SMBasciiID;
    strcpy(p + 1, password);
    p = p + strlen(password) + 2;
    *p = SMBasciiID;
    strcpy(p + 1, device);

    /* Now send the packet and sit back ... */

    if (RFCNB_Send(Con_Handle -> Trans_Connect, pkt, pkt_len) < 0) {

#ifdef DEBUG
        fprintf(stderr, "Error sending TCon request\n");
#endif

        if (Tree_Handle == NULL)
            free(tree);
        RFCNB_Free_Pkt(pkt);
        SMBlib_errno = -SMBlibE_SendFailed;
        return(NULL);

    }

    /* Now get the response ... */

    if (RFCNB_Recv(Con_Handle -> Trans_Connect, pkt, pkt_len) < 0) {

#ifdef DEBUG
        fprintf(stderr, "Error receiving response to TCon\n");
#endif

        if (Tree_Handle == NULL)
            free(tree);
        RFCNB_Free_Pkt(pkt);
        SMBlib_errno = -SMBlibE_RecvFailed;
        return(NULL);

    }

    /* Check out the response type ... */

    if (CVAL(SMB_Hdr(pkt), SMB_hdr_rcls_offset) != SMBC_SUCCESS) {  /* Process error */

#ifdef DEBUG
        fprintf(stderr, "SMB_TCon failed with errorclass = %i, Error Code = %i\n",
                CVAL(SMB_Hdr(pkt), SMB_hdr_rcls_offset),
                SVAL(SMB_Hdr(pkt), SMB_hdr_err_offset));
#endif

        if (Tree_Handle == NULL)
            free(tree);
        SMBlib_SMB_Error = IVAL(SMB_Hdr(pkt), SMB_hdr_rcls_offset);
        RFCNB_Free_Pkt(pkt);
        SMBlib_errno = SMBlibE_Remote;
        return(NULL);

    }

    tree -> tid = SVAL(SMB_Hdr(pkt), SMB_tconr_tid_offset);
    tree -> mbs = SVAL(SMB_Hdr(pkt), SMB_tconr_mbs_offset);

#ifdef DEBUG
    fprintf(stderr, "TConn succeeded, with TID=%i, Max Xmit=%i\n",
            tree -> tid, tree -> mbs);
#endif

    /* Now link the Tree to the Server Structure ... */

    if (Con_Handle -> first_tree == NULL) {

        Con_Handle -> first_tree = tree;
        Con_Handle -> last_tree = tree;

    } else {

        Con_Handle -> last_tree -> next = tree;
        tree -> prev = Con_Handle -> last_tree;
        Con_Handle -> last_tree = tree;

    }

    RFCNB_Free_Pkt(pkt);
    return(tree);

}