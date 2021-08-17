# Makefile for an eosio smart contact

CC=eosio-cpp
CONTRACT=anchortest
ACCOUNT=anchortests1
TEST_URL=https://wax-test.eosdac.io

build:
	$(CC) -D=HYDRA_SKIP_HELPERS=1 -abigen -I include -R resource -contract $(CONTRACT) -o $(CONTRACT).wasm src/$(CONTRACT).cpp

test:
	$(CC) -abigen -I include -R resource -contract $(CONTRACT) -o $(CONTRACT).wasm src/$(CONTRACT).cpp
	yarn test

clean:
	rm -f $(CONTRACT).wast
	rm -f $(CONTRACT).abi
	rm -f $(CONTRACT).wasm

deploy-test:
	cleos -u ${TEST_URL} set contract ${ACCOUNT} . $(CONTRACT).wasm $(CONTRACT).abi -p ${ACCOUNT}@active

install-test: clean build deploy-test

