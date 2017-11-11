static TSort *prepare(apr_pool_t *p,TSortData *pItems,int nItems)
{
    TSort *pData=apr_palloc(p,nItems*sizeof *pData);
    int n;
    
    qsort(pItems,nItems,sizeof *pItems,crude_order);
    for(n=0 ; n < nItems ; ++n) {
	pData[n].nPredecessors=0;
	pData[n].ppPredecessors=apr_pcalloc(p,nItems*sizeof *pData[n].ppPredecessors);
	pData[n].pNext=NULL;
	pData[n].pData=&pItems[n];
    }

    for(n=0 ; n < nItems ; ++n) {
	int i,k;

	for(i=0 ; pItems[n].aszPredecessors && pItems[n].aszPredecessors[i] ; ++i)
	    for(k=0 ; k < nItems ; ++k)
		if(!strcmp(pItems[k].szName,pItems[n].aszPredecessors[i])) {
		    int l;

		    for(l=0 ; l < pData[n].nPredecessors ; ++l)
			if(pData[n].ppPredecessors[l] == &pData[k])
			    goto got_it;
		    pData[n].ppPredecessors[pData[n].nPredecessors]=&pData[k];
		    ++pData[n].nPredecessors;
		got_it:
		    break;
		}
	for(i=0 ; pItems[n].aszSuccessors && pItems[n].aszSuccessors[i] ; ++i)
	    for(k=0 ; k < nItems ; ++k)
		if(!strcmp(pItems[k].szName,pItems[n].aszSuccessors[i])) {
		    int l;

		    for(l=0 ; l < pData[k].nPredecessors ; ++l)
			if(pData[k].ppPredecessors[l] == &pData[n])
			    goto got_it2;
		    pData[k].ppPredecessors[pData[k].nPredecessors]=&pData[n];
		    ++pData[k].nPredecessors;
		got_it2:
		    break;
		}
    }

    return pData;
}