#pragma once

#include <eosio/asset.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>

#include "hydra.hpp"

using namespace std;
using namespace eosio;

CONTRACT anchortest : public contract {
public:
  using contract::contract;

  enum logical_operator : uint8_t { all = 0, any = 1 };

  enum comparison_operator : uint8_t {
    eq = 0,
    ne = 1,
    gt = 2,
    ge = 3,
    lt = 4,
    le = 5
  };

  struct COLLECTION_HOLDINGS {
    name collection_name;
    uint8_t comparison_operator;
    uint32_t amount;
  };

  struct TEMPLATE_HOLDINGS {
    name collection_name;
    uint32_t template_id;
    uint8_t comparison_operator;
    uint32_t amount;
  };

  struct SCHEMA_HOLDINGS {
    name collection_name;
    name schema_name;
    uint8_t comparison_operator;
    uint32_t amount;
  };

  struct TOKEN_HOLDING {
    name token_contract;
    symbol token_symbol;
    uint8_t comparison_operator;
    asset amount;
  };

  using FILTER = std::variant<TOKEN_HOLDING, TEMPLATE_HOLDINGS,
                              COLLECTION_HOLDINGS, SCHEMA_HOLDINGS>;

  struct LOGICAL_GROUP {
    uint8_t logical_operator;
    vector<FILTER> filters;
  };

  ACTION addproofown(name authorized_account, LOGICAL_GROUP group);

  ACTION delproofown(name authorized_account, uint64_t own_id);

  HYDRA_FIXTURE_ACTION(((proofown)(proofown_s)(proofown_t)))

private:
  TABLE proofown_s {
    uint64_t own_id;
    LOGICAL_GROUP group;

    uint64_t primary_key() const { return own_id; };

    EOSLIB_SERIALIZE(proofown_s, (own_id)(group))
  };

  typedef multi_index<name("proofown"), proofown_s> proofown_t;

  // Table instances
  proofown_t proof_of_ownerships = proofown_t(get_self(), get_self().value);
};
