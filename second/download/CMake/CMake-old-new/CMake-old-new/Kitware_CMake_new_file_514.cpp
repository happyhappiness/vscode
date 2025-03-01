/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmComputeLinkDepends.h"

#include "cmComputeComponentGraph.h"
#include "cmGlobalGenerator.h"
#include "cmLocalGenerator.h"
#include "cmMakefile.h"
#include "cmTarget.h"
#include "cmake.h"

#include <cmsys/stl/algorithm>

#include <assert.h>

/*

This file computes an ordered list of link items to use when linking a
single target in one configuration.  Each link item is identified by
the string naming it.  A graph of dependencies is created in which
each node corresponds to one item and directed eges lead from nodes to
those which must *follow* them on the link line.  For example, the
graph

  A -> B -> C

will lead to the link line order

  A B C

The set of items placed in the graph is formed with a breadth-first
search of the link dependencies starting from the main target.

There are two types of items: those with known direct dependencies and
those without known dependencies.  We will call the two types "known
items" and "unknown items", respecitvely.  Known items are those whose
names correspond to targets (built or imported) and those for which an
old-style <item>_LIB_DEPENDS variable is defined.  All other items are
unknown and we must infer dependencies for them.  For items that look
like flags (beginning with '-') we trivially infer no dependencies,
and do not include them in the dependencies of other items.

Known items have dependency lists ordered based on how the user
specified them.  We can use this order to infer potential dependencies
of unknown items.  For example, if link items A and B are unknown and
items X and Y are known, then we might have the following dependency
lists:

  X: Y A B
  Y: A B

The explicitly known dependencies form graph edges

  X -> Y  ,  X -> A  ,  X -> B  ,  Y -> A  ,  Y -> B

We can also infer the edge

  A -> B

because *every* time A appears B is seen on its right.  We do not know
whether A really needs symbols from B to link, but it *might* so we
must preserve their order.  This is the case also for the following
explict lists:

  X: A B Y
  Y: A B

Here, A is followed by the set {B,Y} in one list, and {B} in the other
list.  The intersection of these sets is {B}, so we can infer that A
depends on at most B.  Meanwhile B is followed by the set {Y} in one
list and {} in the other.  The intersection is {} so we can infer that
B has no dependencies.

Let's make a more complex example by adding unknown item C and
considering these dependency lists:

  X: A B Y C
  Y: A C B

The explicit edges are

  X -> Y  ,  X -> A  ,  X -> B  ,  X -> C  ,  Y -> A  ,  Y -> B  ,  Y -> C

For the unknown items, we infer dependencies by looking at the
"follow" sets:

  A: intersect( {B,Y,C} , {C,B} ) = {B,C} ; infer edges  A -> B  ,  A -> C
  B: intersect( {Y,C}   , {}    ) = {}    ; infer no edges
  C: intersect( {}      , {B}   ) = {}    ; infer no edges

Note that targets are never inferred as dependees because outside
libraries should not depend on them.

------------------------------------------------------------------------------

The initial exploration of dependencies using a BFS associates an
integer index with each link item.  When the graph is built outgoing
edges are sorted by this index.

After the initial exploration of the link interface tree, any
transitive (dependent) shared libraries that were encountered and not
included in the interface are processed in their own BFS.  This BFS
follows only the dependent library lists and not the link interfaces.
They are added to the link items with a mark indicating that the are
transitive dependencies.  Then cmComputeLinkInformation deals with
them on a per-platform basis.

The complete graph formed from all known and inferred dependencies may
not be acyclic, so an acyclic version must be created.
The original graph is converted to a directed acyclic graph in which
each node corresponds to a strongly connected component of the
original graph.  For example, the dependency graph

  X -> A -> B -> C -> A -> Y

contains strongly connected components {X}, {A,B,C}, and {Y}.  The
implied directed acyclic graph (DAG) is

  {X} -> {A,B,C} -> {Y}

We then compute a topological order for the DAG nodes to serve as a
reference for satisfying dependencies efficiently.  We perform the DFS
in reverse order and assign topological order indices counting down so
that the result is as close to the original BFS order as possible
without violating dependencies.

------------------------------------------------------------------------------

The final link entry order is constructed as follows.  We first walk
through and emit the *original* link line as specified by the user.
As each item is emitted, a set of pending nodes in the component DAG
is maintained.  When a pending component has been completely seen, it
is removed from the pending set and its dependencies (following edges
of the DAG) are added.  A trivial component (those with one item) is
complete as soon as its item is seen.  A non-trivial component (one
with more than one item; assumed to be static libraries) is complete
when *all* its entries have been seen *twice* (all entries seen once,
then all entries seen again, not just each entry twice).  A pending
component tracks which items have been seen and a count of how many
times the component needs to be seen (once for trivial components,
twice for non-trivial).  If at any time another component finishes and
re-adds an already pending component, the pending component is reset
so that it needs to be seen in its entirety again.  This ensures that
all dependencies of a component are satisified no matter where it
appears.

After the original link line has been completed, we append to it the
remaining pending components and their dependencies.  This is done by
repeatedly emitting the first item from the first pending component
and following the same update rules as when traversing the original
link line.  Since the pending components are kept in topological order
they are emitted with minimal repeats (we do not want to emit a
component just to have it added again when another component is
completed later).  This process continues until no pending components
remain.  We know it will terminate because the component graph is
guaranteed to be acyclic.

The final list of items produced by this procedure consists of the
original user link line followed by minimal additional items needed to
satisfy dependencies.

*/

//----------------------------------------------------------------------------
cmComputeLinkDepends
::cmComputeLinkDepends(cmTarget* target, const char* config)
{
  // Store context information.
  this->Target = target;
  this->Makefile = this->Target->GetMakefile();
  this->LocalGenerator = this->Makefile->GetLocalGenerator();
  this->GlobalGenerator = this->LocalGenerator->GetGlobalGenerator();
  this->CMakeInstance = this->GlobalGenerator->GetCMakeInstance();

  // The configuration being linked.
  this->Config = (config && *config)? config : 0;

  // Enable debug mode if requested.
  this->DebugMode = this->Makefile->IsOn("CMAKE_LINK_DEPENDS_DEBUG_MODE");

  // Assume no compatibility until set.
  this->OldLinkDirMode = false;

  // No computation has been done.
  this->CCG = 0;
}

//----------------------------------------------------------------------------
cmComputeLinkDepends::~cmComputeLinkDepends()
{
  for(std::vector<DependSetList*>::iterator
        i = this->InferredDependSets.begin();
      i != this->InferredDependSets.end(); ++i)
    {
    delete *i;
    }
  delete this->CCG;
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::SetOldLinkDirMode(bool b)
{
  this->OldLinkDirMode = b;
}

//----------------------------------------------------------------------------
std::vector<cmComputeLinkDepends::LinkEntry> const&
cmComputeLinkDepends::Compute()
{
  // Follow the link dependencies of the target to be linked.
  this->AddTargetLinkEntries(-1, this->Target->GetOriginalLinkLibraries());

  // Complete the breadth-first search of dependencies.
  while(!this->BFSQueue.empty())
    {
    // Get the next entry.
    BFSEntry qe = this->BFSQueue.front();
    this->BFSQueue.pop();

    // Follow the entry's dependencies.
    this->FollowLinkEntry(qe);
    }

  // Complete the search of shared library dependencies.
  while(!this->SharedDepQueue.empty())
    {
    // Handle the next entry.
    this->HandleSharedDependency(this->SharedDepQueue.front());
    this->SharedDepQueue.pop();
    }

  // Infer dependencies of targets for which they were not known.
  this->InferDependencies();

  // Cleanup the constraint graph.
  this->CleanConstraintGraph();

  // Display the constraint graph.
  if(this->DebugMode)
    {
    fprintf(stderr,
            "---------------------------------------"
            "---------------------------------------\n");
    fprintf(stderr, "Link dependency analysis for target %s, config %s\n",
            this->Target->GetName(), this->Config?this->Config:"noconfig");
    this->DisplayConstraintGraph();
    }

  // Compute the final ordering.
  this->OrderLinkEntires();

  // Compute the final set of link entries.
  for(std::vector<int>::const_iterator li = this->FinalLinkOrder.begin();
      li != this->FinalLinkOrder.end(); ++li)
    {
    this->FinalLinkEntries.push_back(this->EntryList[*li]);
    }

  // Display the final set.
  if(this->DebugMode)
    {
    this->DisplayFinalEntries();
    }

  return this->FinalLinkEntries;
}

//----------------------------------------------------------------------------
std::map<cmStdString, int>::iterator
cmComputeLinkDepends::AllocateLinkEntry(std::string const& item)
{
  std::map<cmStdString, int>::value_type
    index_entry(item, static_cast<int>(this->EntryList.size()));
  std::map<cmStdString, int>::iterator
    lei = this->LinkEntryIndex.insert(index_entry).first;
  this->EntryList.push_back(LinkEntry());
  this->InferredDependSets.push_back(0);
  this->EntryConstraintGraph.push_back(NodeList());
  return lei;
}

//----------------------------------------------------------------------------
int cmComputeLinkDepends::AddLinkEntry(std::string const& item)
{
  // Check if the item entry has already been added.
  std::map<cmStdString, int>::iterator lei = this->LinkEntryIndex.find(item);
  if(lei != this->LinkEntryIndex.end())
    {
    // Yes.  We do not need to follow the item's dependencies again.
    return lei->second;
    }

  // Allocate a spot for the item entry.
  lei = this->AllocateLinkEntry(item);

  // Initialize the item entry.
  int index = lei->second;
  LinkEntry& entry = this->EntryList[index];
  entry.Item = item;
  entry.Target = this->FindTargetToLink(entry.Item.c_str());
  entry.IsFlag = !entry.Target && item[0] == '-';

  // If the item has dependencies queue it to follow them.
  if(entry.Target)
    {
    // Target dependencies are always known.  Follow them.
    BFSEntry qe = {index, 0};
    this->BFSQueue.push(qe);
    }
  else
    {
    // Look for an old-style <item>_LIB_DEPENDS variable.
    std::string var = entry.Item;
    var += "_LIB_DEPENDS";
    if(const char* val = this->Makefile->GetDefinition(var.c_str()))
      {
      // The item dependencies are known.  Follow them.
      BFSEntry qe = {index, val};
      this->BFSQueue.push(qe);
      }
    else if(!entry.IsFlag)
      {
      // The item dependencies are not known.  We need to infer them.
      this->InferredDependSets[index] = new DependSetList;
      }
    }

  return index;
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::FollowLinkEntry(BFSEntry const& qe)
{
  // Get this entry representation.
  int depender_index = qe.Index;
  LinkEntry const& entry = this->EntryList[depender_index];

  // Follow the item's dependencies.
  if(entry.Target)
    {
    // Follow the target dependencies.
    if(cmTargetLinkInterface const* iface =
       entry.Target->GetLinkInterface(this->Config))
      {
      // This target provides its own link interface information.
      this->AddLinkEntries(depender_index, iface->Libraries);

      // Handle dependent shared libraries.
      this->QueueSharedDependencies(depender_index, iface->SharedDeps);
      }
    else if(!entry.Target->IsImported() &&
            entry.Target->GetType() != cmTarget::EXECUTABLE)
      {
      // Use the target's link implementation as the interface.
      this->AddTargetLinkEntries(depender_index,
                                 entry.Target->GetOriginalLinkLibraries());
      }
    }
  else
    {
    // Follow the old-style dependency list.
    this->AddVarLinkEntries(depender_index, qe.LibDepends);
    }
}

//----------------------------------------------------------------------------
void
cmComputeLinkDepends
::QueueSharedDependencies(int depender_index,
                          std::vector<std::string> const& deps)
{
  for(std::vector<std::string>::const_iterator li = deps.begin();
      li != deps.end(); ++li)
    {
    SharedDepEntry qe;
    qe.Item = *li;
    qe.DependerIndex = depender_index;
    this->SharedDepQueue.push(qe);
    }
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::HandleSharedDependency(SharedDepEntry const& dep)
{
  // Check if the target already has an entry.
  std::map<cmStdString, int>::iterator lei =
    this->LinkEntryIndex.find(dep.Item);
  if(lei == this->LinkEntryIndex.end())
    {
    // Allocate a spot for the item entry.
    lei = this->AllocateLinkEntry(dep.Item);

    // Initialize the item entry.
    LinkEntry& entry = this->EntryList[lei->second];
    entry.Item = dep.Item;
    entry.Target = this->FindTargetToLink(dep.Item.c_str());

    // This item was added specifically because it is a dependent
    // shared library.  It may get special treatment
    // in cmComputeLinkInformation.
    entry.IsSharedDep = true;
    }

  // Get the link entry for this target.
  int index = lei->second;
  LinkEntry& entry = this->EntryList[index];

  // This shared library dependency must follow the item that listed
  // it.
  this->EntryConstraintGraph[dep.DependerIndex].push_back(index);

  // Target items may have their own dependencies.
  if(entry.Target)
    {
    if(cmTargetLinkInterface const* iface =
       entry.Target->GetLinkInterface(this->Config))
      {
      // We use just the shared dependencies, not the interface.
      this->QueueSharedDependencies(index, iface->SharedDeps);
      }
    }
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::AddVarLinkEntries(int depender_index,
                                             const char* value)
{
  // This is called to add the dependencies named by
  // <item>_LIB_DEPENDS.  The variable contains a semicolon-separated
  // list.  The list contains link-type;item pairs and just items.
  std::vector<std::string> deplist;
  cmSystemTools::ExpandListArgument(value, deplist);

  // Compute which library configuration to link.
  cmTarget::LinkLibraryType linkType = cmTarget::OPTIMIZED;
  if(this->Config && cmSystemTools::UpperCase(this->Config) == "DEBUG")
    {
    linkType = cmTarget::DEBUG;
    }

  // Look for entries meant for this configuration.
  std::vector<std::string> actual_libs;
  cmTarget::LinkLibraryType llt = cmTarget::GENERAL;
  bool haveLLT = false;
  for(std::vector<std::string>::const_iterator di = deplist.begin();
      di != deplist.end(); ++di)
    {
    if(*di == "debug")
      {
      llt = cmTarget::DEBUG;
      haveLLT = true;
      }
    else if(*di == "optimized")
      {
      llt = cmTarget::OPTIMIZED;
      haveLLT = true;
      }
    else if(*di == "general")
      {
      llt = cmTarget::GENERAL;
      haveLLT = true;
      }
    else if(!di->empty())
      {
      // If no explicit link type was given prior to this entry then
      // check if the entry has its own link type variable.  This is
      // needed for compatibility with dependency files generated by
      // the export_library_dependencies command from CMake 2.4 and
      // lower.
      if(!haveLLT)
        {
        std::string var = *di;
        var += "_LINK_TYPE";
        if(const char* val = this->Makefile->GetDefinition(var.c_str()))
          {
          if(strcmp(val, "debug") == 0)
            {
            llt = cmTarget::DEBUG;
            }
          else if(strcmp(val, "optimized") == 0)
            {
            llt = cmTarget::OPTIMIZED;
            }
          }
        }

      // If the library is meant for this link type then use it.
      if(llt == cmTarget::GENERAL || llt == linkType)
        {
        actual_libs.push_back(*di);
        }
      else if(this->OldLinkDirMode)
        {
        this->CheckWrongConfigItem(*di);
        }

      // Reset the link type until another explicit type is given.
      llt = cmTarget::GENERAL;
      haveLLT = false;
      }
    }

  // Add the entries from this list.
  this->AddLinkEntries(depender_index, actual_libs);
}

//----------------------------------------------------------------------------
void
cmComputeLinkDepends::AddTargetLinkEntries(int depender_index,
                                           LinkLibraryVectorType const& libs)
{
  // Compute which library configuration to link.
  cmTarget::LinkLibraryType linkType = cmTarget::OPTIMIZED;
  if(this->Config && cmSystemTools::UpperCase(this->Config) == "DEBUG")
    {
    linkType = cmTarget::DEBUG;
    }

  // Look for entries meant for this configuration.
  std::vector<std::string> actual_libs;
  for(cmTarget::LinkLibraryVectorType::const_iterator li = libs.begin();
      li != libs.end(); ++li)
    {
    if(li->second == cmTarget::GENERAL || li->second == linkType)
      {
      actual_libs.push_back(li->first);
      }
    else if(this->OldLinkDirMode)
      {
      this->CheckWrongConfigItem(li->first);
      }
    }

  // Add these entries.
  this->AddLinkEntries(depender_index, actual_libs);
}

//----------------------------------------------------------------------------
void
cmComputeLinkDepends::AddLinkEntries(int depender_index,
                                     std::vector<std::string> const& libs)
{
  // Track inferred dependency sets implied by this list.
  std::map<int, DependSet> dependSets;

  // Loop over the libraries linked directly by the depender.
  for(std::vector<std::string>::const_iterator li = libs.begin();
      li != libs.end(); ++li)
    {
    // Skip entries that will resolve to the target getting linked or
    // are empty.
    std::string item = this->CleanItemName(*li);
    if(item == this->Target->GetName() || item.empty())
      {
      continue;
      }

    // Add a link entry for this item.
    int dependee_index = this->AddLinkEntry(item);

    // The dependee must come after the depender.
    if(depender_index >= 0)
      {
      if(!this->EntryList[dependee_index].IsFlag)
        {
        this->EntryConstraintGraph[depender_index].push_back(dependee_index);
        }
      }
    else
      {
      // This is a direct dependency of the target being linked.
      this->OriginalEntries.push_back(dependee_index);
      }

    // Update the inferred dependencies for earlier items.
    for(std::map<int, DependSet>::iterator dsi = dependSets.begin();
        dsi != dependSets.end(); ++dsi)
      {
      // Add this item to the inferred dependencies of other items.
      // Target items are never inferred dependees because unknown
      // items are outside libraries that should not be depending on
      // targets.
      if(!this->EntryList[dependee_index].Target &&
         !this->EntryList[dependee_index].IsFlag &&
         dependee_index != dsi->first)
        {
        dsi->second.insert(dependee_index);
        }
      }

    // If this item needs to have dependencies inferred, do so.
    if(this->InferredDependSets[dependee_index])
      {
      // Make sure an entry exists to hold the set for the item.
      dependSets[dependee_index];
      }
    }

  // Store the inferred dependency sets discovered for this list.
  for(std::map<int, DependSet>::iterator dsi = dependSets.begin();
      dsi != dependSets.end(); ++dsi)
    {
    this->InferredDependSets[dsi->first]->push_back(dsi->second);
    }
}

//----------------------------------------------------------------------------
std::string cmComputeLinkDepends::CleanItemName(std::string const& item)
{
  // Strip whitespace off the library names because we used to do this
  // in case variables were expanded at generate time.  We no longer
  // do the expansion but users link to libraries like " ${VAR} ".
  std::string lib = item;
  std::string::size_type pos = lib.find_first_not_of(" \t\r\n");
  if(pos != lib.npos)
    {
    lib = lib.substr(pos, lib.npos);
    }
  pos = lib.find_last_not_of(" \t\r\n");
  if(pos != lib.npos)
    {
    lib = lib.substr(0, pos+1);
    }
  if(lib != item)
    {
    switch(this->Target->GetPolicyStatusCMP0004())
      {
      case cmPolicies::WARN:
        {
        cmOStringStream w;
        w << (this->Makefile->GetPolicies()
              ->GetPolicyWarning(cmPolicies::CMP0004)) << "\n"
          << "Target \"" << this->Target->GetName() << "\" links to item \""
          << item << "\" which has leading or trailing whitespace.";
        this->CMakeInstance->IssueMessage(cmake::AUTHOR_WARNING, w.str(),
                                          this->Target->GetBacktrace());
        }
      case cmPolicies::OLD:
        break;
      case cmPolicies::NEW:
        {
        cmOStringStream e;
        e << "Target \"" << this->Target->GetName() << "\" links to item \""
          << item << "\" which has leading or trailing whitespace.  "
          << "This is now an error according to policy CMP0004.";
        this->CMakeInstance->IssueMessage(cmake::FATAL_ERROR, e.str(),
                                          this->Target->GetBacktrace());
        }
        break;
      case cmPolicies::REQUIRED_IF_USED:
      case cmPolicies::REQUIRED_ALWAYS:
        {
        cmOStringStream e;
        e << (this->Makefile->GetPolicies()
              ->GetRequiredPolicyError(cmPolicies::CMP0004)) << "\n"
          << "Target \"" << this->Target->GetName() << "\" links to item \""
          << item << "\" which has leading or trailing whitespace.";
        this->CMakeInstance->IssueMessage(cmake::FATAL_ERROR, e.str(),
                                          this->Target->GetBacktrace());
        }
        break;
      }
    }
  return lib;
}

//----------------------------------------------------------------------------
cmTarget* cmComputeLinkDepends::FindTargetToLink(const char* name)
{
  // Look for a target.
  cmTarget* tgt = this->Makefile->FindTargetToUse(name);

  // Skip targets that will not really be linked.  This is probably a
  // name conflict between an external library and an executable
  // within the project.
  if(tgt && tgt->GetType() == cmTarget::EXECUTABLE &&
     !tgt->IsExecutableWithExports())
    {
    tgt = 0;
    }

  // Return the target found, if any.
  return tgt;
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::InferDependencies()
{
  // The inferred dependency sets for each item list the possible
  // dependencies.  The intersection of the sets for one item form its
  // inferred dependencies.
  for(unsigned int depender_index=0;
      depender_index < this->InferredDependSets.size(); ++depender_index)
    {
    // Skip items for which dependencies do not need to be inferred or
    // for which the inferred dependency sets are empty.
    DependSetList* sets = this->InferredDependSets[depender_index];
    if(!sets || sets->empty())
      {
      continue;
      }

    // Intersect the sets for this item.
    DependSetList::const_iterator i = sets->begin();
    DependSet common = *i;
    for(++i; i != sets->end(); ++i)
      {
      DependSet intersection;
      cmsys_stl::set_intersection
        (common.begin(), common.end(), i->begin(), i->end(),
         std::inserter(intersection, intersection.begin()));
      common = intersection;
      }

    // Add the inferred dependencies to the graph.
    for(DependSet::const_iterator j = common.begin(); j != common.end(); ++j)
      {
      int dependee_index = *j;
      this->EntryConstraintGraph[depender_index].push_back(dependee_index);
      }
    }
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::CleanConstraintGraph()
{
  for(Graph::iterator i = this->EntryConstraintGraph.begin();
      i != this->EntryConstraintGraph.end(); ++i)
    {
    // Sort the outgoing edges for each graph node so that the
    // original order will be preserved as much as possible.
    cmsys_stl::sort(i->begin(), i->end());

    // Make the edge list unique.
    NodeList::iterator last = cmsys_stl::unique(i->begin(), i->end());
    i->erase(last, i->end());
    }
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::DisplayConstraintGraph()
{
  // Display the graph nodes and their edges.
  cmOStringStream e;
  for(unsigned int i=0; i < this->EntryConstraintGraph.size(); ++i)
    {
    NodeList const& nl = this->EntryConstraintGraph[i];
    e << "item " << i << " is [" << this->EntryList[i].Item << "]\n";
    for(NodeList::const_iterator j = nl.begin(); j != nl.end(); ++j)
      {
      e << "  item " << *j << " must follow it\n";
      }
    }
  fprintf(stderr, "%s\n", e.str().c_str());
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::OrderLinkEntires()
{
  // Compute the DAG of strongly connected components.  The algorithm
  // used by cmComputeComponentGraph should identify the components in
  // the same order in which the items were originally discovered in
  // the BFS.  This should preserve the original order when no
  // constraints disallow it.
  this->CCG = new cmComputeComponentGraph(this->EntryConstraintGraph);

  // The component graph is guaranteed to be acyclic.  Start a DFS
  // from every entry to compute a topological order for the
  // components.
  Graph const& cgraph = this->CCG->GetComponentGraph();
  int n = static_cast<int>(cgraph.size());
  this->ComponentVisited.resize(cgraph.size(), 0);
  this->ComponentOrder.resize(cgraph.size(), n);
  this->ComponentOrderId = n;
  // Run in reverse order so the topological order will preserve the
  // original order where there are no constraints.
  for(int c = n-1; c >= 0; --c)
    {
    this->VisitComponent(c);
    }

  // Display the component graph.
  if(this->DebugMode)
    {
    this->DisplayComponents();
    }

  // Start with the original link line.
  for(std::vector<int>::const_iterator i = this->OriginalEntries.begin();
      i != this->OriginalEntries.end(); ++i)
    {
    this->VisitEntry(*i);
    }

  // Now explore anything left pending.  Since the component graph is
  // guaranteed to be acyclic we know this will terminate.
  while(!this->PendingComponents.empty())
    {
    // Visit one entry from the first pending component.  The visit
    // logic will update the pending components accordingly.  Since
    // the pending components are kept in topological order this will
    // not repeat one.
    int e = *this->PendingComponents.begin()->second.Entries.begin();
    this->VisitEntry(e);
    }
}

//----------------------------------------------------------------------------
void
cmComputeLinkDepends::DisplayComponents()
{
  fprintf(stderr, "The strongly connected components are:\n");
  std::vector<NodeList> const& components = this->CCG->GetComponents();
  for(unsigned int c=0; c < components.size(); ++c)
    {
    fprintf(stderr, "Component (%u):\n", c);
    NodeList const& nl = components[c];
    for(NodeList::const_iterator ni = nl.begin(); ni != nl.end(); ++ni)
      {
      int i = *ni;
      fprintf(stderr, "  item %d [%s]\n", i,
              this->EntryList[i].Item.c_str());
      }
    NodeList const& ol = this->CCG->GetComponentGraphEdges(c);
    for(NodeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
      {
      fprintf(stderr, "  followed by Component (%d)\n", *oi);
      }
    fprintf(stderr, "  topo order index %d\n",
            this->ComponentOrder[c]);
    }
  fprintf(stderr, "\n");
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::VisitComponent(unsigned int c)
{
  // Check if the node has already been visited.
  if(this->ComponentVisited[c])
    {
    return;
    }

  // We are now visiting this component so mark it.
  this->ComponentVisited[c] = 1;

  // Visit the neighbors of the component first.
  // Run in reverse order so the topological order will preserve the
  // original order where there are no constraints.
  NodeList const& nl = this->CCG->GetComponentGraphEdges(c);
  for(NodeList::const_reverse_iterator ni = nl.rbegin();
      ni != nl.rend(); ++ni)
    {
    this->VisitComponent(*ni);
    }

  // Assign an ordering id to this component.
  this->ComponentOrder[c] = --this->ComponentOrderId;
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::VisitEntry(int index)
{
  // Include this entry on the link line.
  this->FinalLinkOrder.push_back(index);

  // This entry has now been seen.  Update its component.
  bool completed = false;
  int component = this->CCG->GetComponentMap()[index];
  std::map<int, PendingComponent>::iterator mi =
    this->PendingComponents.find(this->ComponentOrder[component]);
  if(mi != this->PendingComponents.end())
    {
    // The entry is in an already pending component.
    PendingComponent& pc = mi->second;

    // Remove the entry from those pending in its component.
    pc.Entries.erase(index);
    if(pc.Entries.empty())
      {
      // The complete component has been seen since it was last needed.
      --pc.Count;

      if(pc.Count == 0)
        {
        // The component has been completed.
        this->PendingComponents.erase(mi);
        completed = true;
        }
      else
        {
        // The whole component needs to be seen again.
        NodeList const& nl = this->CCG->GetComponent(component);
        assert(nl.size() > 1);
        pc.Entries.insert(nl.begin(), nl.end());
        }
      }
    }
  else
    {
    // The entry is not in an already pending component.
    NodeList const& nl = this->CCG->GetComponent(component);
    if(nl.size() > 1)
      {
      // This is a non-trivial component.  It is now pending.
      PendingComponent& pc = this->MakePendingComponent(component);

      // The starting entry has already been seen.
      pc.Entries.erase(index);
      }
    else
      {
      // This is a trivial component, so it is already complete.
      completed = true;
      }
    }

  // If the entry completed a component, the component's dependencies
  // are now pending.
  if(completed)
    {
    NodeList const& ol = this->CCG->GetComponentGraphEdges(component);
    for(NodeList::const_iterator oi = ol.begin(); oi != ol.end(); ++oi)
      {
      // This entire component is now pending no matter whether it has
      // been partially seen already.
      this->MakePendingComponent(*oi);
      }
    }
}

//----------------------------------------------------------------------------
cmComputeLinkDepends::PendingComponent&
cmComputeLinkDepends::MakePendingComponent(unsigned int component)
{
  // Create an entry (in topological order) for the component.
  PendingComponent& pc =
    this->PendingComponents[this->ComponentOrder[component]];
  pc.Id = component;
  NodeList const& nl = this->CCG->GetComponent(component);

  if(nl.size() == 1)
    {
    // Trivial components need be seen only once.
    pc.Count = 1;
    }
  else
    {
    // This is a non-trivial strongly connected component of the
    // original graph.  It consists of two or more libraries
    // (archives) that mutually require objects from one another.  In
    // the worst case we may have to repeat the list of libraries as
    // many times as there are object files in the biggest archive.
    // For now we just list them twice.
    //
    // The list of items in the component has been sorted by the order
    // of discovery in the original BFS of dependencies.  This has the
    // advantage that the item directly linked by a target requiring
    // this component will come first which minimizes the number of
    // repeats needed.
    pc.Count = 2;
    }

  // Store the entries to be seen.
  pc.Entries.insert(nl.begin(), nl.end());

  return pc;
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::DisplayFinalEntries()
{
  fprintf(stderr, "target [%s] links to:\n", this->Target->GetName());
  for(std::vector<LinkEntry>::const_iterator lei =
        this->FinalLinkEntries.begin();
      lei != this->FinalLinkEntries.end(); ++lei)
    {
    if(lei->Target)
      {
      fprintf(stderr, "  target [%s]\n", lei->Target->GetName());
      }
    else
      {
      fprintf(stderr, "  item [%s]\n", lei->Item.c_str());
      }
    }
  fprintf(stderr, "\n");
}

//----------------------------------------------------------------------------
void cmComputeLinkDepends::CheckWrongConfigItem(std::string const& item)
{
  if(!this->OldLinkDirMode)
    {
    return;
    }

  // For CMake 2.4 bug-compatibility we need to consider the output
  // directories of targets linked in another configuration as link
  // directories.
  if(cmTarget* tgt = this->FindTargetToLink(item.c_str()))
    {
    if(!tgt->IsImported())
      {
      this->OldWrongConfigItems.insert(tgt);
      }
    }
}
