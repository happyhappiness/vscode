{
         parent[i] = -1;
         nHeap++;
         heap[nHeap] = i;
         UPHEAP(nHeap);
      }