const { loadConfig, Blockchain } = require('@klevoya/hydra');

const config = loadConfig('hydra.yml');

describe('Anchor tests', () => {
  const blockchain = new Blockchain(config);
  const tester = blockchain.createAccount('anchortests1');
  const testAccount = blockchain.createAccount('testaccount');

  beforeAll(async () => {
    tester.setContract(blockchain.contractTemplates.anchortest);
  });

  beforeEach(async () => {
    tester.resetTables();
  });

  it('should add proof of ownership record', async () => {
    expect.assertions(2);

    expect(tester.getTableRowsScoped('proofown').anchortests1).toBeUndefined();

    await tester.contract.addproofown({
      authorized_account: testAccount.accountName,
      group: {
        logical_operator: 0,
        filters: [
          ["COLLECTION_HOLDINGS", { collection_name: 'alpacaworlds', comparison_operator: 3, amount: 1 } ]
        ]
      }
    },
    [{
      actor: testAccount.accountName,
      permission: "active"
    }]);

    expect(tester.getTableRowsScoped('proofown').anchortests1).toEqual([
      {
        own_id : '0',
        group: {
          logical_operator: 0,
          filters: [
            ["COLLECTION_HOLDINGS", { collection_name: 'alpacaworlds', comparison_operator: 3, amount: 1 } ]
          ]
        }
      }
    ]);
  });

  it('should delete proof of ownership record', async () => {
    expect.assertions(2);

    await tester.loadFixtures('proofown', require('./fixtures/anchortest/proofown.json'));

    expect(tester.getTableRowsScoped('proofown').anchortests1).toHaveLength(1);

    await tester.contract.delproofown({
      authorized_account: testAccount.accountName,
      own_id: 1,
    },
    [{
      actor: testAccount.accountName,
      permission: "active"
    }]);

    expect(tester.getTableRowsScoped('proofown').anchortests1).toBeUndefined();
  });
});
