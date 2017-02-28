#include <cassert>
#include "leveldb/db.h"
#include <iostream>
using namespace std;
int main() {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());
    std::string value = "leveldb_test";
    std::string value2;
    string key1 = "key";
    leveldb::Status s = db->Put(leveldb::WriteOptions(), key1, value);
    if (s.ok()) s = db->Get(leveldb::ReadOptions(), key1, &value2);
    cout << " key:" << key1 << " value:" << value2 << endl;
//    if (s.ok()) s = db->Delete(leveldb::WriteOptions(), key1);
    delete db;
    return -1;
}
