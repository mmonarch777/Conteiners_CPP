#include "../system/system_methods.ipp"
#include "__service.ipp"

template <class T>
std::vector<int> upper_bound_test(std::set<T> st) {
    std::vector<int> v;
    std::set<int, std::greater<int> > st2;
    st.insert(10);
    st2.insert(10);
    if (st.upper_bound(11) == st.end())
        v.push_back(1);
    if (st2.upper_bound(1) == st2.end())
        v.push_back(1);
    st.insert(20);
    st.insert(30);
    st.insert(40);
    st.insert(50);
    st.insert(60);
    st2.insert(20);
    st2.insert(30);
    st2.insert(40);
    st2.insert(50);
    st2.insert(60);
    std::set<int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = st.upper_bound(i);
        v.push_back(*it);
    }
    for (int i = 11; i < 70; i += 10) {
        it = st2.upper_bound(i);
        v.push_back(*it);
    }

    g_start1 = timer();
    g_end1 = timer();
    return v;
}

template <class T>
std::vector<int> upper_bound_test(_set<T> st) {
    std::vector<int> v;
    _set<int, std::greater<int> > st2;
    st.insert(10);
    st2.insert(10);
    if (st.upper_bound(11) == st.end())
        v.push_back(1);
    if (st2.upper_bound(1) == st2.end())
        v.push_back(1);
    st.insert(20);
    st.insert(30);
    st.insert(40);
    st.insert(50);
    st.insert(60);
    st2.insert(20);
    st2.insert(30);
    st2.insert(40);
    st2.insert(50);
    st2.insert(60);
    _set<int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = st.upper_bound(i);
        v.push_back(*it);
    }
    for (int i = 11; i < 70; i += 10) {
        it = st2.upper_bound(i);
        v.push_back(*it);
    }

    g_start2 = timer();
    g_end2 = timer();
    return v;
}

int main() {

    exit(run_set_unit_test<int>("upper_bound()", upper_bound_test, upper_bound_test));
}