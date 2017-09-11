namespace xgboost {
namespace sync {

int GetRank(void) {
  return MPI::COMM_WORLD.Get_rank();
}
