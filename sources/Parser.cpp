// Copyright 2020 Timoshenko Yulia timoshenkojulie01@gmail.com
#include "Parser.hpp"
const int accBegin = 8;
const int accLength = 8;
const int dateBigin = 17;
const int dateLength = 8;
const int balanceLength = 17;
Parser::Parser(std::string path) {
  if (path != "") {
    if (bfs::exists(path)) {
      pathToFtp = bfs::path{path};
    }
  } else {
    pathToFtp = bfs::current_path();
  }// Copyright 2020 Timoshenko Yulia timoshenkojulie01@gmail.com
#include "Parser.hpp"
const int accBegin = 8;
const int accLength = 8;
const int dateBigin = 17;
const int dateLength = 8;
const int balanceLength = 7;
Parser::Parser(std::string path) {
  if (path != "") {
    if (bfs::exists(path)) {
      pathToFtp = bfs::path{path};
    }
  } else {
    pathToFtp = bfs::current_path();
  }
  for (bfs::directory_entry &x : bfs::directory_iterator{pathToFtp}) {
    if (bfs::is_directory(x)) {
      for (bfs::directory_entry &y : bfs::directory_iterator{x}) {
        if (is_directory(y)) {
          cycle(y);
        } else {
          if (nameIsCor(y)) {
            std::string dir = directory(y);
            std::string name = y.path().stem().string();
            addBalance(name, dir);
          }
        }
      }
    }
  }
}

bool Parser::nameIsCor(const bfs::path &y) {
  std::string name = y.stem().string();
  std::string ext = y.extension().string();
  if (name.length() != 25) return false;
  if (name.substr(0, balanceLength) != "balance") return false;
  if (name[balanceLength] != '_') return false;
  if (!(isNumber(name.substr(accBegin, accLength)))) return false;
  if (name[16] != '_') return false;
  if (!(isNumber(name.substr(dateBigin, dateLength)))) return false;
  return (ext == ".txt");
}
void Parser::addBalance(const std::string &name, const std::string &dir) {
  std::string key = name.substr(accBegin, accLength);
  if (balance.count(key) == 0) {
    std::vector<std::string> dates;
    dates.push_back(name.substr(dateBigin, dateLength));
    balance[key] = {dir, dates};
  } else {
    balance[key].second.push_back(name.substr(dateBigin, dateLength));
  }
}
void Parser::cycle(const bfs::directory_entry &x) {
  for (bfs::directory_entry &y : bfs::directory_iterator{x}) {
    if (is_directory(y)) {
      cycle(y);
    } else {
      if (nameIsCor(y)) {
        std::string dir = directory(y);
        std::string name = y.path().stem().string();

        addBalance(name, dir);
      }
    }
  }
}

bool Parser::isNumber(const std::string &s) {
  bool k = 1;
  for (char i : s) {
    if (i < '0' || i > '9') k = 0;
  }
  return k;
}
std::string Parser::directory(const bfs::path &p) {
  std::string s = p.string();
  std::string dir = "";
  size_t i = s.length() - 1;
  while (s[i] != '/') i--;
  i--;
  while (s[i] != '/') {
    dir = s[i] + dir;
    i--;
  }
  return dir;
}
std::string Parser::getBroker(const std::string &key) {
  return balance[key].first;
}

std::ostream &operator<<(std::ostream &out, const Parser &A) {
  for (auto &it : A.balance) {
    for (auto &i : it.second.second) {
      out << it.second.first << " balance_" << it.first << "_" << i << ".txt"
          << '\n';
    }
  }
  for (auto &it : A.balance) {
    std::string max = it.second.second[0];

    for (const auto &i : it.second.second) {
      if (i > max) max = i;
    }
    out << "broker: " << it.second.first << " account: " << it.first
        << " files: " << it.second.second.size() << " lastdate: " << max
        << '\n';
  }
  return out;
}
  for (bfs::directory_entry &x : bfs::directory_iterator{pathToFtp}) {
    if (bfs::is_directory(x)) {
      for (bfs::directory_entry &y : bfs::directory_iterator{x}) {
        if (is_directory(y)) {
          cycle(y);
        } else {
          if (nameIsCor(y)) {
            std::string dir = directory(y);
            std::string name = y.path().stem().string();
            addBalance(name, dir);
          }
        }
      }
    }
  }
}

bool Parser::nameIsCor(const bfs::path &y) {
  std::string name = y.stem().string();
  std::string ext = y.extension().string();
  if (name.length() != 25) return false;
  if (name.substr(0, balanceLength) != "balance") return false;
  if (name[balanceLength] != '_') return false;
  if (!(isNumber(name.substr(accBegin, accLength)))) return false;
  if (name[16] != '_') return false;
  if (!(isNumber(name.substr(dateBigin, dateLength)))) return false;
  return (ext == ".txt");
}
void Parser::addBalance(const std::string &name, const std::string &dir) {
  std::string key = name.substr(accBegin, accLength);
  if (balance.count(key) == 0) {
    std::vector<std::string> dates;
    dates.push_back(name.substr(dateBigin, dateLength));
    balance[key] = {dir, dates};
  } else {
    balance[key].second.push_back(name.substr(dateBigin, dateLength));
  }
}
void Parser::cycle(const bfs::directory_entry &x) {
  for (bfs::directory_entry &y : bfs::directory_iterator{x}) {
    if (is_directory(y)) {
      cycle(y);
    } else {
      if (nameIsCor(y)) {
        std::string dir = directory(y);
        std::string name = y.path().stem().string();

        addBalance(name, dir);
      }
    }
  }
}

bool Parser::isNumber(const std::string &s) {
  bool k = 1;
  for (char i : s) {
    if (i < '0' || i > '9') k = 0;
  }
  return k;
}
std::string Parser::directory(const bfs::path &p) {
  std::string s = p.string();
  std::string dir = "";
  size_t i = s.length() - 1;
  while (s[i] != '/') i--;
  i--;
  while (s[i] != '/') {
    dir = s[i] + dir;
    i--;
  }
  return dir;
}
std::string Parser::getBroker(const std::string& key) {
  return balance[key].first;
}

std::ostream &operator<<(std::ostream &out, const Parser &A) {
  for (auto &it : A.balance) {
    for (auto &i : it.second.second) {
      out << it.second.first << " balance_" << it.first << "_" << i << ".txt"
          << '\n';
    }
  }
  for (auto &it : A.balance) {
    std::string max = it.second.second[0];

    for (const auto &i : it.second.second) {
      if (i > max) max = i;
    }
    out << "broker: " << it.second.first << " account: " << it.first
        << " files: " << it.second.second.size() << " lastdate: " << max
        << '\n';
  }
  return out;
}
