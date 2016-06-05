/*
 * Author: Qiao Zhang
 * Date: 20160218
 */

#include "util.hpp"
#include "DictionaryTrie.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include <fstream>
#include <sstream>

void testStudent(std::string dict_filename){

    std::ifstream in;
    in.open(dict_filename, std::ios::binary);


    // Testing student's trie
    std::cout << "\nTiming your solution" << std::endl;
    std::cout << "\nLoading dictionary..." << std::endl;
    DictionaryTrie* dictionary_trie = new DictionaryTrie();

    Utils::load_dict(*dictionary_trie, in);

    std::cout << "Finished loading dictionary." << std::endl;
    std::cout << "\nStarting timing tests for your solution." << std::endl;

    Timer T;
    std::vector<std::string> results;
    long long time_duration;

    // Test 1
    std::cout << "\n\tTest 1: prefix= \"*iterating through alphabet*\", num_completions= 10" << std::endl;
    T.begin_timer();
    int count = 0;
    results = dictionary_trie->predictCompletions("a",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("b",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("c",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("d",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("e",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("f",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("g",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("h",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("i",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("j",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("k",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("l",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("m",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("n",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("o",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("p",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("q",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("r",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("s",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("t",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("u",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("v",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("w",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("x",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("y",10);
    count += results.size();
    results = dictionary_trie->predictCompletions("z",10);
    count += results.size();
    time_duration = T.end_timer();
    std::cout << "\tTest 1: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 1: results found: " <<  count << std::endl;

    // Test 2
    std::cout << "\n\tTest 2: prefix= \"a\", num_completions= 10" << std::endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("a",10);
    time_duration = T.end_timer();
    std::cout << "\tTest 2: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 2: results found: " <<  results.size() << std::endl;

    // Test 3
    std::cout << "\n\tTest 3: prefix= \"the\", num_completions= 10" << std::endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("the",10);
    time_duration = T.end_timer();
    std::cout << "\tTest 3: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 3: results found: " <<  results.size() << std::endl;

    // Test 4
    std::cout << "\n\tTest 4: prefix= \"app\", num_completions= 10" << std::endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("app",10);
    time_duration = T.end_timer();
    std::cout << "\tTest 4: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 4: results found: " <<  results.size() << std::endl;

    // Test 5
    std::cout << "\n\tTest 5: prefix= \"man\", num_completions= 10" << std::endl;
    T.begin_timer();
    results = dictionary_trie->predictCompletions("man",10);
    time_duration = T.end_timer();
    std::cout << "\tTest 5: time taken: " << time_duration << " nanoseconds." << std::endl;
    std::cout << "\tTest 5: results found: " <<  results.size() << std::endl;

    std::cout << "\nWould you like to run additional tests? y/n\n";
    std::string response;
    std::getline(std::cin, response);

    if(response.compare("y") == 0){
        std::string prefix;
        std::string ws;
        int num_completions;

        std::cout << "\nAdditional user tests." << std::endl;
        std::cout << "Enter prefix: ";

        while(std::getline(std::cin, prefix)){

            std::cout << "Enter num_completions: ";
            std::getline(std::cin, ws);
            num_completions = stoi(ws);

            std::cout << "\n\tUser Test: prefix= \"" << prefix << "\" num_completions= " << num_completions << std::endl;
            T.begin_timer();
            results = dictionary_trie->predictCompletions(prefix,num_completions);
            time_duration = T.end_timer();
            std::cout << "\tUser Test: time taken: " << time_duration << " nanoseconds." << std::endl;
            std::cout << "\tUser Test: results found: " <<  results.size() << "\n\n";
            std::cout << "Enter prefix: ";

        }

    }




    std::cout << "\nFinished timing your solution." << std::endl;
    delete dictionary_trie;


}

int main(int argc, char *argv[]) {

    if(argc < 5){
        std::cout << "Incorrect number of arguments." << std::endl;
        std::cout << "\t ./benchdict min_size step_size num_iterations dictfile" << std::endl;
        std::cout << std::endl;
        exit(-1);
    }

    int num_iterations = std::stoi(argv[3]);
    int min_size = std::stoi(argv[1]);
    int step_size = std::stoi(argv[2]);
    std::string dictfilename = argv[4];

    //testStudent(dictfilename);

    /* test dictionary BST*/
    std::cout << "Benchmarking Dictionary BST." << std::endl;
    for(int iter = 0; iter < num_iterations; iter++){

        DictionaryBST bst;
        std::ifstream in;
        in.open(dictfilename, std::ios::binary);
        Utils::load_dict(bst, in, min_size + iter * step_size);

        Timer T;
        long long time_duration;
        T.begin_timer();
        bst.find("asdfghj");
        bst.find("qwertyuii");
        bst.find("zcxvvbnmkl");
        bst.find("poinhfhueuwiwdklv");
        bst.find("rutohbndbsbsj");
        bst.find("apple");
        bst.find("ugfbejdoofvjssb");
        bst.find("battleman");
        bst.find("abbreviation");
        bst.find("anthropology");
        time_duration = T.end_timer() / 10;

        std::cout << min_size + iter * step_size << "\t" << time_duration << std::endl;
    }

    /* test dictionary Hashtable*/
    std::cout << "Benchmarking Dictionary Hashtable." << std::endl;
    for(int iter = 0; iter < num_iterations; iter++){

        DictionaryHashtable hash;
        std::ifstream in;
        in.open(dictfilename, std::ios::binary);
        Utils::load_dict(hash, in, min_size + iter * step_size);

        Timer T;
        long long time_duration;
        T.begin_timer();
        hash.find("asdfghj");
        hash.find("qwertyuii");
        hash.find("zcxvvbnmkl");
        hash.find("poinhfhueuwiwdklv");
        hash.find("rutohbndbsbsj");
        hash.find("apple");
        hash.find("ugfbejdoofvjssb");
        hash.find("battleman");
        hash.find("abbreviation");
        hash.find("anthropology");
        time_duration = T.end_timer() / 10;

        std::cout << min_size + iter * step_size << "\t" << time_duration << std::endl;
    }

    /* test dictionary Multi-way Trie*/
    std::cout << "Benchmarking Dictionary Trie." << std::endl;
    for(int iter = 0; iter < num_iterations; iter++){

        DictionaryTrie trie;
        std::ifstream in;
        in.open(dictfilename, std::ios::binary);
        Utils::load_dict(trie, in, min_size + iter * step_size);

        Timer T;
        long long time_duration;
        T.begin_timer();
        trie.find("asdfghj");
        trie.find("qwertyuii");
        trie.find("zcxvvbnmkl");
        trie.find("poinhfhueuwiwdklv");
        trie.find("rutohbndbsbsj");
        trie.find("apple");
        trie.find("ugfbejdoofvjssb");
        trie.find("battleman");
        trie.find("abbreviation");
        trie.find("anthropology");
        time_duration = T.end_timer() / 10;

        std::cout << min_size + iter * step_size << "\t" << time_duration << std::endl;
    }

    return 0;

}