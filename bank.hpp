#ifndef BANK_HPP
#define BANK_HPP

#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

struct AccountException : public std::invalid_argument {
  explicit AccountException(const std::string& msg)
      : std::invalid_argument(msg) {}
};

template <typename T>
class BankAccount {
 public:
  BankAccount(int accountId, std::string ownerName)
      : accountId(accountId), ownerName(std::move(ownerName)), balance(0) {}

  int getId() const { return accountId; }
  T getBalance() const { return balance; }
  std::string getOwner() const { return ownerName; }

  void deposit(T amount) {
    if (amount < 0) {
      throw AccountException("negative amount");
    }
    balance += amount;
  }

  void withdraw(T amount) {
    if (amount < 0) {
      throw AccountException("negative amount");
    }
    if (amount > balance) {
      throw AccountException("insufficient amount");
    }
    balance -= amount;
  }

 private:
  const int accountId;
  const std::string ownerName;
  T balance;
};

template <typename T>
std::ostream& operator<<(std::ostream& s, const BankAccount<T>& account) {
  s << "#" << account.getId() << ", owner: '" << account.getOwner()
    << "', balance: " << account.getBalance();
  return s;
}

template <typename T>
class Bank {
 public:
  explicit Bank(std::string name) : name(std::move(name)), nextAccountId(1) {}

  int createNewAccount(const std::string ownerName) {
    int id = nextAccountId++;
    accounts.emplace(id, BankAccount<T>(id, ownerName));
    return id;
  }

  BankAccount<T> getAccount(int accountId) const {
    return accounts.at(accountId);
  }

  int getNumAccounts() const { return accounts.size(); }

  void deposit(int accountId, T amount) {
    BankAccount<T>& account = accounts.at(accountId);
    account.deposit(amount);
  }

  void withdraw(int accountId, T amount) {
    BankAccount<T>& account = accounts.at(accountId);
    account.withdraw(amount);
  }

  void transfer(int debitAccountId, int creditAccountId, T amount) {
    BankAccount<T>& debitAccount = accounts.at(debitAccountId);
    BankAccount<T>& creditAccount = accounts.at(creditAccountId);
    debitAccount.withdraw(amount);
    creditAccount.deposit(amount);
  }

 private:
  const std::string name;
  int nextAccountId;
  std::map<int, BankAccount<T> > accounts;
};

#endif  // BANK_HPP
