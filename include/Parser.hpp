// Copyright 2020 Timoshenko Yulia timoshenkojulie01@gmail.com
#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_
#include <boost/filesystem.hpp>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
namespace bfs = boost::filesystem;

class Parser {
  bfs::path pathToFtp;
  std::map<std::string, std::pair<std::string, std::vector<std::string>>>
      balance;
  static bool nameIsCor(const bfs::path &y);
  static bool isNumber(const std::string &s);
  static std::string directory(const bfs::path &);
  void addBalance(const std::string &name, const std::string &dir);
  void cycle(const bfs::directory_entry &x);

 public:
  explicit Parser(std::string path);
  std::string getBroker(const std::string &);
  friend std::ostream &operator<<(std::ostream &out, const Parser &A);
};

#endif  // INCLUDE_PARSER_HPP_
