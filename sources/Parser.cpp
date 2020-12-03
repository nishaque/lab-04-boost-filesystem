// Copyright 2020 Timoshenko Yulia timoshenkojulie01@gmail.com

#include "Parser.hpp"

Parser::Parser(std::string path) {
    if (path != "") {
        if (bfs::exists(path)) {
            pathToFtp = bfs::path{path};
        }
    } else {
        pathToFtp = bfs::current_path();
    }

    std::cout << pathToFtp.string();
    for (bfs::directory_entry &x : bfs::directory_iterator{pathToFtp}) {
        if (bfs::is_directory(x)) {
            for (bfs::directory_entry &y : bfs::directory_iterator{x}) {
                if (is_directory(y))
                    cycle(y);
                else {
                    if (nameIsCor(y)) {
                        std::string dir = directory(y);

                        std::cout << dir << " " << y.path().stem().string()
                                  << y.path().extension().string() << std::endl;
                        std::string name = y.path().stem().string();

                        addBalance(name, dir);
                    }
                }
            }
        }
    }
    print();
}

bool Parser::nameIsCor(const bfs::path &y) {
    std::string name = y.stem().string();
    std::string ext = y.extension().string();
    if (name.length() != 25)
        return false;
    if (name.substr(0, 7) != "balance")
        return false;
    if (name[7] != '_')
        return false;
    if (!(isNumber(name.substr(8, 8))))
        return false;
    if (name[16] != '_')
        return false;
    if (!(isNumber(name.substr(17, 8))))
        return false;
    return (ext == ".txt");
}
void Parser::addBalance(const std::string &name, const std::string &dir) {
    std::string key = name.substr(8, 8);
    std::string num = name.substr(17, 8);
    if (balance.count(key) == 0) {
        std::vector<std::string> dates;
        dates.push_back(name.substr(17, 8));
        balance[key] = {dir, dates};
    } else {
        balance[key].second.push_back(name.substr(17, 8));
    }
}
void Parser::cycle(const bfs::directory_entry &x) {
    for (bfs::directory_entry &y : bfs::directory_iterator{x}) {
        if (is_directory(y))
            cycle(y);
        else {
            if (nameIsCor(y)) {
                std::string dir = directory(y);

                std::cout << dir << " " << y.path().stem().string()
                          << y.path().extension().string() << std::endl;
                std::string name = y.path().stem().string();

                addBalance(name, dir);
            }
        }
    }
}

void Parser::print() {
    for (auto &it : balance) {
        std::string max = it.second.second[0];

        for (const auto &i : it.second.second) {
            if (i > max)
                max = i;
        }
        std::cout << "broker: " << it.second.first << " account: " << it.first
                  << " files: " << it.second.second.size() << " lastdate: " << max
                  << '\n';
    }
}

bool Parser::isNumber(const std::string &s) {
    bool k = 1;
    for (char i : s) {
        if (i < '0' || i > '9')
            k = 0;
    }
    return k;
}
std::string Parser::directory(const bfs::path &p) {
    std::string s = p.string();
    std::string dir = "";
    size_t i = s.length() - 1;
    while (s[i] != '/')
        i--;
    i--;
    while (s[i] != '/') {
        dir = s[i] + dir;
        i--;
    }
    return dir;
}
std::string Parser::getBroker(std::string key) { return balance[key].first; }
