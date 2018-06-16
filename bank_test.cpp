#include "bank.hpp"
#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

TEST(Bank, EmptyBank) {
  Bank<int> bank("CreditBank");
  EXPECT_EQ(0, bank.getNumAccounts());
}

TEST(Bank, CreateAccount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  EXPECT_EQ(1, bank.getNumAccounts());
}

TEST(Bank, GetExistingAccount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  auto account = bank.getAccount(accountId);
  EXPECT_EQ(accountId, account.getId());
}

TEST(Bank, GetNonExistingAccount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  EXPECT_THROW(bank.getAccount(accountId + 1),
               std::out_of_range);  // will not exist
}

TEST(Bank, GetAccoutsNotLeaking) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  auto account1 = bank.getAccount(accountId);
  account1.deposit(100);
  auto account2 = bank.getAccount(accountId);
  EXPECT_EQ(0, account2.getBalance());
}

TEST(Bank, DepsositIntoExistingAccount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  bank.deposit(accountId, 100);
  EXPECT_EQ(100, bank.getAccount(accountId).getBalance());
}

TEST(Bank, DepsositIntoNonExistingAccount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  EXPECT_THROW(bank.deposit(accountId + 1, 100), std::out_of_range);
}

TEST(Bank, DepsositNegativeAmount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  EXPECT_THROW(bank.deposit(accountId, -100), AccountException);
}

TEST(Bank, WithdrawFromoExistingAccount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  bank.deposit(accountId, 100);
  bank.withdraw(accountId, 50);
  EXPECT_EQ(50, bank.getAccount(accountId).getBalance());
}

TEST(Bank, WithdrawmFromNonExistingAccount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  EXPECT_THROW(bank.deposit(accountId + 1, 100), std::out_of_range);
}

TEST(Bank, WithdrawNegativeAmount) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  EXPECT_THROW(bank.withdraw(accountId, -100), AccountException);
}

TEST(Bank, WithdrawInsufficentFunds) {
  Bank<int> bank("CreditBank");
  int accountId = bank.createNewAccount("Bob Smith");
  EXPECT_EQ(1, accountId);
  bank.deposit(accountId, 100);
  EXPECT_THROW(bank.withdraw(accountId, 200), AccountException);
}

TEST(Bank, Transfer) {
  Bank<int> bank("CreditBank");
  int account1 = bank.createNewAccount("John Smith");
  int account2 = bank.createNewAccount("Jane Doe");
  bank.deposit(account1, 100);
  bank.transfer(account1, account2, 25);
  EXPECT_EQ(75, bank.getAccount(account1).getBalance());
  EXPECT_EQ(25, bank.getAccount(account2).getBalance());
}

TEST(Bank, TransferInsufficentFunds) {
  Bank<int> bank("CreditBank");
  int account1 = bank.createNewAccount("John Smith");
  int account2 = bank.createNewAccount("Jane Doe");
  bank.deposit(account1, 100);
  EXPECT_THROW(bank.transfer(account1, account2, 150), AccountException);
}

TEST(Bank, TransferNegativeAmount) {
  Bank<int> bank("CreditBank");
  int account1 = bank.createNewAccount("John Smith");
  int account2 = bank.createNewAccount("Jane Doe");
  bank.deposit(account1, 100);
  EXPECT_THROW(bank.transfer(account1, account2, -100), AccountException);
}

TEST(Bank, TransferFromNonExistingAccount) {
  Bank<int> bank("CreditBank");
  int account1 = bank.createNewAccount("John Smith");
  int account2 = bank.createNewAccount("Jane Doe");
  EXPECT_THROW(bank.transfer(account1 + 1000, account2, 1), std::out_of_range);
}

TEST(Bank, TransferToNonExistingAccount) {
  Bank<int> bank("CreditBank");
  int account1 = bank.createNewAccount("John Smith");
  int account2 = bank.createNewAccount("Jane Doe");
  EXPECT_THROW(bank.transfer(account1, account2 + 100, 1), std::out_of_range);
}

using ::testing::InitGoogleTest;

int main(int argc, char** argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}