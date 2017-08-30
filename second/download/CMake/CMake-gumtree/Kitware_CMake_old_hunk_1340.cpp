}



//----------------------------------------------------------------------------

void cmComputeTargetDepends::Tarjan()

{

  int n = static_cast<int>(this->TargetDependGraph.size());

  TarjanEntry entry = {0,-1,0};

  this->TarjanEntries.resize(n, entry);

  this->TarjanWalkId = 0;

  this->TarjanVisited.resize(n, 0);

  for(int i = 0; i < n; ++i)

    {

    // Start a new DFS from this node if it has never been visited.

    if(!this->TarjanVisited[i])

      {

      assert(this->TarjanStack.empty());

      ++this->TarjanWalkId;

      this->TarjanIndex = 0;

      this->TarjanVisit(i);

      }

    }

}



//----------------------------------------------------------------------------

void cmComputeTargetDepends::TarjanVisit(int i)

{

  // We are now visiting this node.

  this->TarjanVisited[i] = this->TarjanWalkId;



  // Initialize the entry.

  this->TarjanEntries[i].Root = i;

  this->TarjanEntries[i].Component = -1;

  this->TarjanEntries[i].VisitIndex = ++this->TarjanIndex;

  this->TarjanStack.push(i);



  // Follow outgoing edges.

  TargetDependList const& tdl = this->TargetDependGraph[i];

  for(TargetDependList::const_iterator di = tdl.begin();

      di != tdl.end(); ++di)

    {

    int j = *di;



    // Ignore edges to nodes that have been reached by a previous DFS

    // walk.  Since we did not reach the current node from that walk

    // it must not belong to the same component and it has already

    // been assigned to a component.

    if(this->TarjanVisited[j] > 0 &&

       this->TarjanVisited[j] < this->TarjanWalkId)

      {

      continue;

      }



    // Visit the destination if it has not yet been visited.

    if(!this->TarjanVisited[j])

      {

      this->TarjanVisit(j);

      }



    // If the destination has not yet been assigned to a component,

    // check if it is a better potential root for the current object.

    if(this->TarjanEntries[j].Component < 0)

      {

      if(this->TarjanEntries[this->TarjanEntries[j].Root].VisitIndex <

         this->TarjanEntries[this->TarjanEntries[i].Root].VisitIndex)

        {

        this->TarjanEntries[i].Root = this->TarjanEntries[j].Root;

        }

      }

    }



  // Check if we have found a component.

  if(this->TarjanEntries[i].Root == i)

    {

    // Yes.  Create it.

    int c = static_cast<int>(this->Components.size());

    this->Components.push_back(ComponentList());

    ComponentList& component = this->Components[c];



    // Populate the component list.

    int j;

    do

      {

      // Get the next member of the component.

      j = this->TarjanStack.top();

      this->TarjanStack.pop();



      // Assign the member to the component.

      this->TarjanEntries[j].Component = c;

      this->TarjanEntries[j].Root = i;



      // Store the node in its component.

      component.push_back(j);

      } while(j != i);



    // Sort the component members for clarity.

    std::sort(component.begin(), component.end());

    }

}



//----------------------------------------------------------------------------

void cmComputeTargetDepends::DisplayComponents()

{

  fprintf(stderr, "The strongly connected components are:\n");

  int n = static_cast<int>(this->Components.size());

  for(int c = 0; c < n; ++c)

    {

    ComponentList const& cl = this->Components[c];

    fprintf(stderr, "Component (%d):\n", c);

    for(ComponentList::const_iterator ci = cl.begin();

        ci != cl.end(); ++ci)

      {

      int i = *ci;

      fprintf(stderr, "  contains target %d [%s]\n",

              i, this->Targets[i]->GetName());

      }

