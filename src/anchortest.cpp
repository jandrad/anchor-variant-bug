#include <anchortest.hpp>

ACTION anchortest::addproofown(name authorized_account, LOGICAL_GROUP group) {
  require_auth(authorized_account);
  
  proof_of_ownerships.emplace(authorized_account, [&](auto &_row) {
    _row.own_id = proof_of_ownerships.available_primary_key();
    _row.group = group;
  });
}

ACTION anchortest::delproofown(name authorized_account, uint64_t own_id) {
  require_auth(authorized_account);

  auto itr = proof_of_ownerships.require_find(own_id, "Not record with id found");
  proof_of_ownerships.erase(itr);
}