int count_next_metalink_resource(metalinkfile *mlfile)
{
  int count = 0;
  metalink_resource *res;
  for(res = mlfile->resource; res; res = res->next, ++count);
  return count;
}