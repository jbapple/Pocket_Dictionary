//
// Created by tomer on 10/29/19.
//

#include "benchmark_tests.h"

vector<uint64_t> random_vector(size_t size) {
    random_device rnd_device;
    mt19937_64 mersenne_engine{rnd_device()};
    uniform_int_distribution<u_int64_t> dist{0, ~0ULL};

    auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

    vector<uint64_t> vec(size);
    generate(begin(vec), end(vec), gen);
}

string rand_string(int minLength, int charsNum, int numOfDiffLength) {
    int len = minLength bitor (rand() % numOfDiffLength);
    assert(4 < len);
    char s[len];
    for (int i = 0; i < len; ++i) s[i] = 64 bitor (rand() % charsNum);
    s[len] = 0;
    string res(s);
    return res;
}

void set_init(size_t size, set<string> *mySet, int minLength, int charsNum) {
    for (int i = 0; i < size; ++i) mySet->insert(rand_string(minLength, charsNum));
}

void vec_init(size_t size, vector<uint32_t> *my_vec) {
    random_device rnd_device;
    mt19937 mersenne_engine{rnd_device()};
    uniform_int_distribution<u_int64_t> dist{0, ~0ULL};

    auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };
    my_vec->resize(size);
    generate(begin(*my_vec), end(*my_vec), gen);
}

void vector_lexicographic_init(size_t size, vector<string> *vec, int minLength, int charsNum) {
    size_t start_val = (1ul << (ulong) minLength) - 1;
    for (size_t i = 0; i < size; ++i) vec->push_back(to_string(start_val++));
}

ostream &b0(size_t number_of_pds, float load_factor, size_t f, size_t m, size_t l, size_t lookup_reps, ostream &os) {
    clock_t startRunTime = clock();
    set<string> member_set, nom_set;

    clock_t t0 = clock();
    size_t n = ceil(f * number_of_pds * load_factor);
    set_init(n, &member_set);
    double member_set_init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    pow2c_filter a(number_of_pds, m, f, l);
    double init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : member_set) a.insert(&iter);
    double insertion_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    set_init(lookup_reps, &nom_set);
    double nom_set_init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double set_ratio = nom_set.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
//    for (auto iter : nom_set) ++counter[w.lookup_verifier(&iter, call_adapt)];
    for (auto iter : nom_set) a.lookup(&iter);

    double lookup_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double total_run_time = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);


    test_printer(n, 0, lookup_reps, false, set_ratio, counter, member_set_init_time, nom_set_init_time,
                 init_time, insertion_time, lookup_time, total_run_time, os);

//    os << a;
    return os;

}

ostream &
b0_naive(size_t number_of_pds, float load_factor, size_t f, size_t m, size_t l, size_t lookup_reps, ostream &os) {
    clock_t startRunTime = clock();
    set<string> member_set, nom_set;

    clock_t t0 = clock();
    size_t n = ceil(f * number_of_pds * load_factor);
    set_init(n, &member_set);
    double member_set_init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    pow2c_naive_filter a(number_of_pds, m, f, l);
    double init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : member_set) a.insert(&iter);
    double insertion_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    set_init(lookup_reps, &nom_set);
    double nom_set_init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double set_ratio = nom_set.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
//    for (auto iter : nom_set) ++counter[w.lookup_verifier(&iter, call_adapt)];
    for (auto iter : nom_set) a.lookup(&iter);

    double lookup_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double total_run_time = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);


    test_printer(n, 0, lookup_reps, false, set_ratio, counter, member_set_init_time, nom_set_init_time,
                 init_time, insertion_time, lookup_time, total_run_time, os);

//    os << a;
    return os;

}

ostream &const_filter_rates(size_t number_of_pds, float load_factor, size_t f, size_t m, size_t l, size_t lookup_reps,
                            ostream &os) {
    clock_t startRunTime = clock();
    set<string> member_set, nom_set;

    clock_t t0 = clock();
    size_t n = ceil((double) f * number_of_pds * load_factor);
    set_init(n, &member_set);
    double member_set_init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = clock();
    const_filter a(number_of_pds, m, f, l);
    double init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = clock();
    for (auto iter : member_set) a.insert(&iter);
    double insertion_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = clock();
    set_init(lookup_reps, &nom_set);
    double nom_set_init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;
    double set_ratio = nom_set.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
//    for (auto iter : nom_set) ++counter[w.lookup_verifier(&iter, call_adapt)];
    for (auto iter : nom_set) a.lookup(&iter);

    double lookup_time = (double) (clock() - t0) / (CLOCKS_PER_SEC);
    double total_run_time = (double) (clock() - startRunTime) / (CLOCKS_PER_SEC);


    test_printer(n, 0, lookup_reps, false, set_ratio, counter, member_set_init_time, nom_set_init_time,
                 init_time, insertion_time, lookup_time, total_run_time, os);

//    os << a;
    return os;
}


ostream &
filter_rates(size_t number_of_pds, float load_factor, size_t f, size_t m, size_t l, size_t lookup_reps, ostream &os) {
    auto start_run_time = chrono::high_resolution_clock::now();
    vector<uint32_t > member_vec, nom_vec;

    auto t0 = chrono::high_resolution_clock::now();
    size_t n = ceil((double) f * number_of_pds * load_factor);
    vec_init(n, &member_vec);
    auto t1 = chrono::high_resolution_clock::now();
    auto member_set_init_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    pow2c_filter a(number_of_pds, m, f, l);
    t1 = chrono::high_resolution_clock::now();
    auto init_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    for (auto iter : member_vec) a.insert(iter);
    t1 = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    vec_init(lookup_reps, &nom_vec);
    t1 = chrono::high_resolution_clock::now();
    auto nom_set_init_time = chrono::duration_cast<ns>(t1 - t0).count();
    double set_ratio = nom_vec.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
//    for (auto iter : nom_vec) ++counter[w.lookup_verifier(&iter, call_adapt)];
    t0 = chrono::high_resolution_clock::now();
    for (auto iter : nom_vec) a.lookup(iter);
    t1 = chrono::high_resolution_clock::now();
    auto lookup_time = chrono::duration_cast<ns>(t1 - t0).count();
    auto total_run_time = chrono::duration_cast<ns>(t1 - start_run_time).count();

//    chrono::microseconds
//    a.print_stats();

    test_table(n, 0, lookup_reps, set_ratio, counter, member_set_init_time, nom_set_init_time,
               init_time, insertion_time, lookup_time, total_run_time, os);

//    os << a;
    return os;
}



ostream &const_filter_rates32(size_t number_of_pds, float load_factor, size_t f, size_t m, size_t l, size_t lookup_reps,
                              ostream &os) {
    auto start_run_time = chrono::high_resolution_clock::now();
    vector<uint32_t> member_vec, nom_vec;

    auto t0 = chrono::high_resolution_clock::now();
    size_t n = ceil((double) f * number_of_pds * load_factor);
    vec_init(n, &member_vec);
    auto t1 = chrono::high_resolution_clock::now();
    auto member_set_init_time = chrono::duration_cast<ns>(t1 - t0).count();
//    double member_set_init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = chrono::high_resolution_clock::now();
    const_filter a(number_of_pds, m, f, l);
    t1 = chrono::high_resolution_clock::now();
    auto init_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    for (auto iter : member_vec) a.insert(iter);
    t1 = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    vec_init(lookup_reps, &nom_vec);
    t1 = chrono::high_resolution_clock::now();
    auto nom_set_init_time = chrono::duration_cast<ns>(t1 - t0).count();
    double set_ratio = nom_vec.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
//    for (auto iter : nom_vec) ++counter[w.lookup_verifier(&iter, call_adapt)];
    t0 = chrono::high_resolution_clock::now();
    for (auto iter : nom_vec) a.lookup(iter);
    t1 = chrono::high_resolution_clock::now();
    auto lookup_time = chrono::duration_cast<ns>(t1 - t0).count();
    auto total_run_time = chrono::duration_cast<ns>(t1 - start_run_time).count();

//    chrono::microseconds
//    a.print_stats();

    test_table(n, 0, lookup_reps, set_ratio, counter, member_set_init_time, nom_set_init_time,
               init_time, insertion_time, lookup_time, total_run_time, os);

//    os << a;
    return os;
}


ostream &
cuckoo_filter_rates(size_t number_of_pds, float load_factor, size_t f, size_t m, const size_t l, size_t lookup_reps,
                    ostream &os) {
    auto start_run_time = chrono::high_resolution_clock::now();
    vector<uint32_t> member_vec, nom_vec;

    auto t0 = chrono::high_resolution_clock::now();
    size_t n = ceil((double) f * number_of_pds * load_factor);
    vec_init(n, &member_vec);
    auto t1 = chrono::high_resolution_clock::now();
    auto member_set_init_time = chrono::duration_cast<ns>(t1 - t0).count();
//    double member_set_init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = chrono::high_resolution_clock::now();
    CuckooFilter<uint32_t, 7> a(n);
    t1 = chrono::high_resolution_clock::now();
    auto init_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    for (auto iter : member_vec) a.Add(iter);
    t1 = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    vec_init(lookup_reps, &nom_vec);
    t1 = chrono::high_resolution_clock::now();
    auto nom_set_init_time = chrono::duration_cast<ns>(t1 - t0).count();
    double set_ratio = nom_vec.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
//    for (auto iter : nom_vec) ++counter[w.lookup_verifier(&iter, call_adapt)];
    t0 = chrono::high_resolution_clock::now();
    for (auto iter : nom_vec) a.Contain(iter);
    t1 = chrono::high_resolution_clock::now();
    auto lookup_time = chrono::duration_cast<ns>(t1 - t0).count();
    auto total_run_time = chrono::duration_cast<ns>(t1 - start_run_time).count();
//    chrono::microseconds
    test_table(n, 0, lookup_reps, set_ratio, counter, member_set_init_time, nom_set_init_time,
               init_time, insertion_time, lookup_time, total_run_time, os);

//    os << a;
    return os;
    /*clock_t startRunTime = clock();
    vector<uint32_t> member_vec, nom_vec;

    clock_t t0 = clock();

    size_t total_elements_inserted = ceil((double) f * number_of_pds * load_factor);
    vec_init(total_elements_inserted, &member_vec);
    double member_set_init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = clock();
//    const size_t bits_per_element = l;
    CuckooFilter<uint32_t, 7> a(total_elements_inserted);
//    a(number_of_pds, m, f, l);
    double init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = clock();
    for (auto iter: member_vec) a.Add(iter);
    double insertion_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = clock();
    vec_init(lookup_reps, &nom_vec);
    double nom_set_init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;
    double set_ratio = nom_vec.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
//    for (auto iter : nom_vec) ++counter[w.lookup_verifier(&iter, call_adapt)];
    for (auto iter : nom_vec) a.Contain(iter);

    double lookup_time = (double) (clock() - t0) / (CLOCKS_PER_SEC);
    double total_run_time = (double) (clock() - startRunTime) / (CLOCKS_PER_SEC);


    test_printer(total_elements_inserted, 0, lookup_reps, false, set_ratio, counter, member_set_init_time,
                 nom_set_init_time,
                 init_time, insertion_time, lookup_time, total_run_time, os);

//    os << a;
    return os;
*/
}

template<class T>
ostream &template_rates(size_t number_of_pds, float load_factor, size_t f, size_t m, size_t l, size_t lookup_reps,
                        ostream &os) {
    auto start_run_time = chrono::high_resolution_clock::now();
    vector<uint32_t> member_vec, nom_vec;

    auto t0 = chrono::high_resolution_clock::now();
    size_t n = ceil((double) f * number_of_pds * load_factor);
    vec_init(n, &member_vec);
    auto t1 = chrono::high_resolution_clock::now();
    auto member_set_init_time = chrono::duration_cast<ns>(t1 - t0).count();
//    double member_set_init_time = (double) (clock() - t0) / CLOCKS_PER_SEC;

    t0 = chrono::high_resolution_clock::now();
    T a(number_of_pds, m, f, l);
    t1 = chrono::high_resolution_clock::now();
    auto init_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    for (auto iter : member_vec) a.insert(iter);
    t1 = chrono::high_resolution_clock::now();
    auto insertion_time = chrono::duration_cast<ns>(t1 - t0).count();

    t0 = chrono::high_resolution_clock::now();
    vec_init(lookup_reps, &nom_vec);
    t1 = chrono::high_resolution_clock::now();
    auto nom_set_init_time = chrono::duration_cast<ns>(t1 - t0).count();
    double set_ratio = nom_vec.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
//    for (auto iter : nom_vec) ++counter[w.lookup_verifier(&iter, call_adapt)];
    t0 = chrono::high_resolution_clock::now();
    for (auto iter : nom_vec) a.lookup(iter);
    t1 = chrono::high_resolution_clock::now();
    auto lookup_time = chrono::duration_cast<ns>(t1 - t0).count();
    auto total_run_time = chrono::duration_cast<ns>(t1 - start_run_time).count();

    test_table(n, 0, lookup_reps, set_ratio, counter, member_set_init_time, nom_set_init_time,
               init_time, insertion_time, lookup_time, total_run_time, os);

//    os << a;
    return os;
}


void test_table_header_print() {
    if (!to_print_header)
        return;
    to_print_header = false;
    cout << left;
    cout << setw(WIDTH) << "number of elements";
    cout << setw(WIDTH) << "insertion/millisecond";
    cout << setw(WIDTH) << "lookup/millisecond";
    cout << setw(WIDTH) << "total runtime in millisecond" << endl;
}

/**Old testing function. should make changes for PD*/
ostream &
test_table(size_t n, double eps, size_t lookups_num, double set_ratio, int *counter, ulong member_set_init_time,
           ulong nom_set_init_time, ulong init_time, ulong insertion_time, ulong lookup_time, ulong total_run_time,
           ostream &os) {

    test_table_header_print();
    cout << setw(WIDTH) << n;
    cout << setw(WIDTH) << n / (insertion_time / 1e6);
    cout << setw(WIDTH) << lookups_num / (lookup_time / 1e6);
    cout << setw(WIDTH) << (total_run_time / 1e6) << endl;
    if (set_ratio < 1)
        cout << "\t\t" << "set_ratio is less than 1: " << set_ratio << endl;
    return os;
}

/*void b1(size_t f, size_t m, size_t l, size_t lookup_reps, ostream &os) {
    clock_t startRunTime = clock();
    set<string> member_set, nom_set;

    clock_t t0 = clock();
    set_init(insertion_reps, &member_set);
    double member_set_init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    Wrapper w(n, eps, is_adaptive, remote_name);
    double init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : member_set) w.add(&iter, 0);
    double insertion_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    set_init(lookup_reps, &nom_set);
    double nom_set_init_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double set_ratio = nom_set.size() / (double) lookup_reps;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : nom_set) ++counter[w.lookup_verifier(&iter, call_adapt)];

    double lookup_time = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double total_run_time = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);


    test_printer(n, eps, lookup_reps, is_adaptive, set_ratio, counter, member_set_init_time, nom_set_init_time,
                 init_time, insertion_time, lookup_time, total_run_time, os);

    os << w;
    return os;


}*/



ostream &test_printer(size_t n, double eps, size_t lookups_num, bool is_adaptive, double set_ratio, int *counter,
                      double member_set_init_time, double nom_set_init_time, double init_time, double insertion_time,
                      double lookup_time, double total_run_time, ostream &os) {
//    counter_printer(os, counter);
    string name = "not adaptive";
    if (is_adaptive)
        name = "adaptive";
    double ans = ((double) counter[1]) / lookups_num;
    os << "member_set_init_time: " << member_set_init_time << endl;
    os << "nom_set_init_time: " << nom_set_init_time << endl;
    os << "nom_set to lookups_num ratio : " << set_ratio << endl << endl;
    os << "false positive rate:" << ans;
    os << "\tExpected: " << eps << "\terror deviation: " << 100 * (abs(ans - eps) / eps) << "%" << endl;
//    cout << "false positive rate:" << ans << endl;
    os << name << " init_time: " << init_time << endl;
    cout << "insertion_time: " << insertion_time << "\t" << n / insertion_time << " el/sec.\t";
    os << name << " insertion_time: " << insertion_time << "\t" << n / insertion_time << " el/sec" << endl;
    cout << "lookup_time: " << lookup_time << "\t" << lookups_num / lookup_time << " el/sec.\t";
    os << name << " lookup_time: " << lookup_time << "\t" << lookups_num / lookup_time << " el/sec" << endl << endl;
    os << "total_run_time: " << total_run_time << endl;
    cout << "total_run_time: " << total_run_time << endl;
    return os;
    //    ((double) n) / _helper_init_time << "el per sec" << endl;

}

bool filter_r0(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l) {
    pow2c_filter d = pow2c_filter(number_of_pds, m, f, l);
    vector<string> member_set, non_member_set, to_be_deleted_set;
    auto number_of_elements_in_the_filter = floor(load_factor * number_of_pds * f);
    vector_lexicographic_init(number_of_elements_in_the_filter / 2, &member_set);
    vector_lexicographic_init(number_of_elements_in_the_filter / 2, &to_be_deleted_set);

    for (auto iter : member_set) d.insert(&iter);
    for (auto iter : to_be_deleted_set) d.insert(&iter);

    size_t counter = 0;
    for (auto iter : member_set) {
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }
    for (auto iter : to_be_deleted_set) {
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    for (auto iter : non_member_set) {
        bool c1, c2;
        c1 = find(member_set.begin(), member_set.end(), iter) != member_set.end();
        c2 = find(to_be_deleted_set.begin(), to_be_deleted_set.end(), iter) != to_be_deleted_set.end();
        if (c1 || c2)
            continue;
        if (d.lookup(&iter)) {
            cout << "False Positive:" << endl;
        }
    }

    counter = 0;
    for (auto iter : to_be_deleted_set) {
        d.remove(&iter);
        counter++;
    };

    counter = 0;
    for (auto iter : member_set) {
        bool c = find(to_be_deleted_set.begin(), to_be_deleted_set.end(), iter) != to_be_deleted_set.end();
        if (c)
            continue;
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    return true;

}

bool filter_naive_r0(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l) {
    pow2c_naive_filter d = pow2c_naive_filter(number_of_pds, m, f, l);
    vector<string> member_set, non_member_set, to_be_deleted_set;
    auto number_of_elements_in_the_filter = floor(load_factor * number_of_pds * f);
    vector_lexicographic_init(number_of_elements_in_the_filter / 2, &member_set);
    vector_lexicographic_init(number_of_elements_in_the_filter / 2, &to_be_deleted_set);

    for (auto iter : member_set) d.insert(&iter);
    for (auto iter : to_be_deleted_set) d.insert(&iter);

    size_t counter = 0;
    for (auto iter : member_set) {
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }
    for (auto iter : to_be_deleted_set) {
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    for (auto iter : non_member_set) {
        bool c1, c2;
        c1 = find(member_set.begin(), member_set.end(), iter) != member_set.end();
        c2 = find(to_be_deleted_set.begin(), to_be_deleted_set.end(), iter) != to_be_deleted_set.end();
        if (c1 || c2)
            continue;
        if (d.lookup(&iter)) {
            cout << "False Positive:" << endl;
        }
    }

    counter = 0;
    for (auto iter : to_be_deleted_set) {
        d.remove(&iter);
        counter++;
    };

    counter = 0;
    for (auto iter : member_set) {
        bool c = find(to_be_deleted_set.begin(), to_be_deleted_set.end(), iter) != to_be_deleted_set.end();
        if (c)
            continue;
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    return true;

}

bool const_filter_r0(size_t number_of_pds, float load_factor, size_t l) {
    size_t f = 32, m = 32;
    const_filter d = const_filter(number_of_pds, m, f, l);
    vector<string> member_set, non_member_set, to_be_deleted_set;
    auto number_of_elements_in_the_filter = floor(load_factor * number_of_pds * f);
    vector_lexicographic_init(number_of_elements_in_the_filter / 2, &member_set);
    vector_lexicographic_init(number_of_elements_in_the_filter / 2, &to_be_deleted_set);

    for (auto iter : member_set) d.insert(&iter);
    for (auto iter : to_be_deleted_set) d.insert(&iter);

    size_t counter = 0;
    for (auto iter : member_set) {
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }
    for (auto iter : to_be_deleted_set) {
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    for (auto iter : non_member_set) {
        bool c1, c2;
        c1 = find(member_set.begin(), member_set.end(), iter) != member_set.end();
        c2 = find(to_be_deleted_set.begin(), to_be_deleted_set.end(), iter) != to_be_deleted_set.end();
        if (c1 || c2)
            continue;
        if (d.lookup(&iter)) {
            cout << "False Positive:" << endl;
        }
    }

    counter = 0;
    for (auto iter : to_be_deleted_set) {
        d.remove(&iter);
        counter++;
    };

    counter = 0;
    for (auto iter : member_set) {
        bool c = find(to_be_deleted_set.begin(), to_be_deleted_set.end(), iter) != to_be_deleted_set.end();
        if (c)
            continue;
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    return true;

}


bool filter_r1(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l) {
    pow2c_filter d = pow2c_filter(number_of_pds, m, f, l);
    set<string> member_set, non_member_set, to_be_deleted_set;
    auto number_of_elements_in_the_filter = floor(load_factor * number_of_pds * f);

    set_init(number_of_elements_in_the_filter / 2, &member_set);
    set_init(number_of_elements_in_the_filter / 2, &to_be_deleted_set);
    set_init(number_of_elements_in_the_filter, &non_member_set);

    for (auto iter : member_set) d.insert(&iter);
    for (auto iter : to_be_deleted_set) d.insert(&iter);

    size_t counter = 0;
    for (auto iter : member_set) {
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }
    for (auto iter : to_be_deleted_set) {
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    for (auto iter : non_member_set) {
        if (member_set.count(iter) || to_be_deleted_set.count(iter))
            continue;
        if (d.lookup(&iter)) {
            cout << "False Positive:" << endl;
        }
    }

    for (auto iter : to_be_deleted_set) d.remove(&iter);

    counter = 0;
    for (auto iter : member_set) {
        if (to_be_deleted_set.count(iter))
            continue;
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    return true;
}

bool filter_naive_r1(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l) {
    pow2c_naive_filter d = pow2c_naive_filter(number_of_pds, m, f, l);
    set<string> member_set, non_member_set, to_be_deleted_set;
    auto number_of_elements_in_the_filter = floor(load_factor * number_of_pds * f);
    set_init(number_of_elements_in_the_filter / 2, &member_set);
    set_init(number_of_elements_in_the_filter / 2, &to_be_deleted_set);
    set_init(number_of_elements_in_the_filter, &non_member_set);

    for (auto iter : member_set) d.insert(&iter);
    for (auto iter : to_be_deleted_set) d.insert(&iter);

    size_t counter = 0;
    for (auto iter : member_set) {
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }
    for (auto iter : to_be_deleted_set) {
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    for (auto iter : non_member_set) {
        if (member_set.count(iter) || to_be_deleted_set.count(iter))
            continue;
        if (d.lookup(&iter)) {
            cout << "False Positive:" << endl;
        }
    }

    for (auto iter : to_be_deleted_set) d.remove(&iter);

    counter = 0;
    for (auto iter : member_set) {
        if (to_be_deleted_set.count(iter))
            continue;
        counter++;
        if (!d.lookup(&iter)) {
            cout << "False negative:" << endl;
            d.lookup(&iter);
            assert(d.lookup(&iter));
        }
    }

    return true;
}
