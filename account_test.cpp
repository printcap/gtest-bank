#include <iostream>
#include <sstream>
#include "bank.hpp"

#include <gtest/gtest.h>

TEST(BankAccount, Constructor) {
  BankAccount<int> account(42, "John Smith");
  EXPECT_EQ(42, account.getId());
  EXPECT_EQ(0, account.getBalance());
  EXPECT_STREQ("John Smith", account.getOwner().c_str());
}

TEST(BankAccount, StreamOperator) {
  BankAccount<int> account(1, "John Smith");
  std::stringstream ss;
  ss << account;
  EXPECT_STREQ("#1, owner: 'John Smith', balance: 0", ss.str().c_str());
}

TEST(BankAccount, Deposit) {
  BankAccount<int> account(1, "John Smith");
  EXPECT_EQ(0, account.getBalance());
  account.deposit(10);
  EXPECT_EQ(10, account.getBalance());
}

TEST(BankAccount, DepositNegativeAmountThrowsException) {
  BankAccount<int> account(1, "John Smith");
  EXPECT_EQ(0, account.getBalance());
  EXPECT_THROW(account.deposit(-10), AccountException);
}

TEST(BankAccount, Withdraw) {
  BankAccount<int> account(1, "John Smith");
  account.deposit(100);
  EXPECT_EQ(100, account.getBalance());
  account.withdraw(20);
  EXPECT_EQ(80, account.getBalance());
}

TEST(BankAccount, WithdrawNegativeAmountThrowsException) {
  BankAccount<int> account(1, "John Smith");
  account.deposit(100);
  EXPECT_EQ(100, account.getBalance());
  EXPECT_THROW(account.withdraw(-20), AccountException);
}

TEST(BankAccount, WithdrawInsufficientAmountThrowsException) {
  BankAccount<int> account(1, "John Smith");
  account.deposit(100);
  EXPECT_EQ(100, account.getBalance());
  EXPECT_THROW(account.withdraw(120), AccountException);
}
