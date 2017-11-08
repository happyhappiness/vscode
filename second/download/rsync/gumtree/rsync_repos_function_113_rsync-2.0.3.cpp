void unmap_file(struct map_struct *map)
{
#ifdef HAVE_MMAP
  if (map->map)
    munmap(map->map,map->size);
#endif
  if (map->p) free(map->p);
  free(map);
}