static TSort *tsort(TSort *pData,int nItems)
{
    int nTotal;
    TSort *pHead=NULL;
    TSort *pTail=NULL;

    for(nTotal=0 ; nTotal < nItems ; ++nTotal) {
	int n,i,k;

	for(n=0 ; ; ++n) {
	    if(n == nItems)
		assert(0);      /* we have a loop... */
	    if(!pData[n].pNext && !pData[n].nPredecessors)
		break;
	}
	if(pTail)
	    pTail->pNext=&pData[n];
	else
	    pHead=&pData[n];
	pTail=&pData[n];
	pTail->pNext=pTail;     /* fudge it so it looks linked */
	for(i=0 ; i < nItems ; ++i)
	    for(k=0 ; pData[i].ppPredecessors[k] ; ++k)
		if(pData[i].ppPredecessors[k] == &pData[n]) {
		    --pData[i].nPredecessors;
		    break;
		}
    }
    pTail->pNext=NULL;  /* unfudge the tail */
    return pHead;
}