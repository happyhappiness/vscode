int SMB_Get_Tree_MBS(SMB_Tree_Handle tree)

{
    if (tree != NULL) {
        return(tree -> mbs);
    } else {
        return(SMBlibE_BAD);
    }
}