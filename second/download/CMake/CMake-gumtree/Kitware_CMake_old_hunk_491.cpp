  fprintf(stderr, "%s\n", e.str().c_str());

}



//----------------------------------------------------------------------------

void cmComputeLinkDepends::OrderLinkEntires()

{

  // Compute the DAG of strongly connected components.  The algorithm

