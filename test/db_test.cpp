#include <string>
#include <vector>
#include <filesystem>
#include "gtest/gtest.h"
#include "db.h"

void clear_dir() {
    std::filesystem::remove_all("/home/parallels/metakv/data/");
    std::filesystem::create_directory("/home/parallels/metakv/data/");
}

// TEST(DB_TEST, basic) {
//     std::shared_ptr<Options> opt = std::make_shared<Options>("/home/parallels/metakv/data/", 1024, 4096, 1024, 0.01);
//     std::shared_ptr<DB> db = std::make_shared<DB>(opt);

//     std::string key1 = "key1";
//     std::string value1 = "value1";
//     db->set(key1, value1);

//     ASSERT_EQ(db->get(key1).compare(value1), 0);

//     std::string key2 = "key2";
//     std::string value2 = "value2";
//     std::string key3 = "key3";
//     std::string value3 = "value3";

//     db->set(key2, value2);
//     db->set(key3, value3);
    
//     ASSERT_EQ(db->get(key2).compare(value2), 0);
//     ASSERT_EQ(db->get(key3).compare(value3), 0);
// }


TEST(DB_TEST, large_write_test) {
    clear_dir();

    std::shared_ptr<Options> opt = std::make_shared<Options>("/home/parallels/metakv/data/", 1024, 4096, 1024, 0.01);
    std::shared_ptr<DB> db = std::make_shared<DB>(opt);


    for (size_t i = 0; i < 50; i++) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        db->set(key, value);
    }

    db->scan();

    for (size_t i = 0; i < 50; i++) {
        std::cout << i << std::endl;
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        ASSERT_EQ(db->get(key).compare(value), 0);
    }
}

int main(int argc, char** argv) {
    clear_dir();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
